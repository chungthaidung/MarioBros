#include "PlayerLevel.h"
#include "CGameObject.h"
#include "GhostObject.h"
#include "debug.h"
#include "CGame.h"
PlayerLevel::PlayerLevel(CMario* mario)
{
	this->mario = mario;
}
void PlayerLevel::Collision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (mario->state != MARIO_STATE_DIE)
		mario->CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		mario->x += mario->dx;
		mario->y += mario->dy;
		mario->onGround = false;
	//	DebugOut(L"Mario dang khong va cham\n");
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		mario->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		mario->x += min_tx * mario->dx + nx * 0.02f;
		mario->y += min_ty * mario->dy + ny * 0.02f;

		if (nx != 0) mario->vx = 0;
		if (ny != 0) {
			mario->vy = 0;
			if (ny < 0) {
				mario->onGround = true;
				//			DebugOut(L"Mario dang dung\n");
			}
		}
	
	}


	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<GhostObject*>(e->obj))
		{
			if (e->nx != 0) {
				mario->x += mario->dx;
			}
			if (e->ny > 0) {
				mario->y += mario->dy;
			}
			else {
				mario->vy = 0;
			}
		}
		else
		{
			if (e->nx != 0) {
				mario->vx = 0;
			}
			if (e->ny != 0)
			{
				mario->vy = 0;
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void PlayerLevel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	MiniJump(dt);
	PowerMeterUpdate(dt);
	MovingState(dt);
	// Calculate dx, dy 
	JumpingState(dt);
	CrouchState(dt);
	AttackState(dt);
	mario->CGameObject::Update(dt);
	// Simple fall down
	mario->vy += MARIO_GRAVITY * dt;
	Collision(coObjects);
	//DebugOut(L"Mario jump state: %d \n", mario->JumpState);
	DebugOut(L"Mario power meter: %f \n", mario->GetPowerMeter());
}
void PlayerLevel::MovingState(DWORD dt)
{	
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_RIGHT) || keyboard->IsKeyDown(DIK_LEFT))
	{
		if (keyboard->IsKeyDown(DIK_RIGHT))
			mario->nx = 1;
		else
			mario->nx = -1;
		if (mario->vx * mario->nx < 0) mario->isSkid = true;
		mario->SetState(MARIO_STATE_WALKING);
		mario->SetAcceleration(MARIO_WALKING_ACCELERATION * mario->nx);
		mario->SetDrag(MARIO_WALK_DRAG_FORCE);
		float maxspeed = MARIO_WALKING_SPEED;
		
		if (keyboard->IsKeyDown(DIK_A))
		{
			if (abs(mario->vx) == MARIO_RUNNING_SPEED)
				mario->SetState(MARIO_STATE_RUNNING);
			mario->SetAcceleration(MARIO_RUNNING_ACCELERATION * mario->nx);
			mario->SetDrag(MARIO_RUN_DRAG_FORCE);
			maxspeed = MARIO_RUNNING_SPEED;
		}

		if (mario->isSkid == 1)
		{
			mario->SetAcceleration(MARIO_SKID_ACCELERATION * mario->nx);
			mario->SetState(MARIO_STATE_SKID);
		}

		mario->vx += mario->GetAcceleration() * mario->dt;
		if (abs(mario->vx) > maxspeed)
		{
			mario->vx = maxspeed * mario->nx;
		}
		if (mario->vx * mario->nx >= 0) mario->isSkid = false;
	}
	else //khong nhan gi 
	{
		if (abs(mario->vx) > mario->GetDrag()*dt)
		{
			mario->vx -= mario->GetDrag() * dt * mario->nx;
		}
		else
		{
			mario->SetState(MARIO_STATE_IDLE);
			mario->vx = 0;
		}
		mario->isSkid = false;
	}
}
void PlayerLevel::JumpingState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float jumpForce = MARIO_JUMP_FORCE;
	mario->SetyPush(MARIO_PUSH_FORCE);
	switch (mario->JumpState)
	{
	case MARIO_STATE_JUMP:
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpHigh)
		{
			jumpForce = MARIO_HIGH_JUMP_FORCE;
		}
		
		if (mario->vy > - jumpForce && mario->canJumpHigh) 
		{ 
			mario->vy -= mario->GetyPush() *dt;
		}
		else
		{
			mario->vy = -jumpForce;
			mario->JumpState = MARIO_STATE_HIGH_JUMP;
		}
		break;
	case MARIO_STATE_HIGH_JUMP:
		if (mario->vy > 0) { 
			mario->JumpState = MARIO_STATE_FALL; 
			mario->canJumpHigh = false;
		}
		break;
	case MARIO_STATE_SUPER_JUMP:
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpSuper)
		{
			jumpForce = MARIO_SUPER_JUMP_FORCE;
		}
		if (mario->vy > -jumpForce && mario->canJumpSuper)
		{
			mario->vy -= mario->GetyPush() * dt;
		}
		else
		{
			mario->vy = -jumpForce;
			mario->JumpState = MARIO_STATE_SUPER_FALL;
		}
		break;
	case MARIO_STATE_SUPER_FALL:
	case MARIO_STATE_FALL:
		if (mario->onGround == true)
		{	
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
		}
		break;
	}
}
void PlayerLevel::PowerMeterUpdate(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float power = mario->GetPowerMeter();
	if (abs(mario->vx)>MARIO_WALKING_SPEED && mario->onGround)
	{
		if (power < 0) power = 0;
		power += MARIO_POWER_METER_UP * dt;
		if (power > MARIO_POWER_METER_MAX + 1)
			power = MARIO_POWER_METER_MAX;
	}
	else if(mario->GetPowerMeter()>0)
	{
		power -= MARIO_POWER_METER_DOWN * dt;
		if (power < 0)
			power = 0;
	}
	mario->SetPowerMeter(power);
}
void PlayerLevel::SetState(int state)
{

}
void PlayerLevel::MiniJump(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_X)&&mario->onGround)
	{
		mario->vy = -MARIO_JUMP_FORCE;
		mario->canJumpHigh = false;
		mario->canJumpSuper = false;
		mario->JumpState = MARIO_STATE_JUMP;
	}
}