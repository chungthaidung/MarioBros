#include "PlayerLevel.h"
#include "CGameObject.h"
#include "GhostObject.h"
#include "debug.h"
#include "CGame.h"
#include "Koopa.h"
PlayerLevel::PlayerLevel(CMario* mario)
{
	this->mario = mario;
}
void PlayerLevel::Update(DWORD dt)
{
	MiniJump();
	PowerMeterUpdate(dt);
	MovingState(dt);
	// Calculate dx, dy 
	JumpingState(dt);
	CrouchState(dt);
	AttackState(dt);
	// Simple fall down
	mario->vy += mario->GetGravity() * dt;
	mario->CGameObject::Update(dt);
//	Collision(coObjects);
	//DebugOut(L"Mario vx: %f \n", mario->vx);
	//DebugOut(L"Mario jump state: %d \n", mario->JumpState);
	//DebugOut(L"Mario power meter: %f \n", mario->GetPowerMeter());
}
void PlayerLevel::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// turn off collision when die 
	if (mario->state != MARIO_STATE_DIE)
		mario->CalcPotentialCollisions(colliable_objects,mario->coEResult);
}
void PlayerLevel::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (mario->coEResult.size() == 0)
	{
		mario->x += mario->dx;
		mario->y += mario->dy;
		mario->onGround = false;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		mario->FilterCollision(mario->coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=mario->dx)
		//	mario->x += nx*abs(rdx); 

		// block every object first!
		mario->x += min_tx * mario->dx + nx * 0.4f;
		mario->y += min_ty * mario->dy + ny * 0.4f;

		if (nx != 0) mario->vx = 0;
		if (ny != 0) {
			mario->vy = 0;
			if (ny < 0) {
				mario->onGround = true;
			}
			if (mario->ny > 0)
			{
				mario->SetGravity(MARIO_GRAVITY);
				mario->vy = 0;
			}
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_CROUCH
				&& mario->GetState()!=MARIO_STATE_CROUCH)
			{
				CGame* keyboard = CGame::GetInstance();
				Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
				if (e->nx != 0 && keyboard->IsKeyDown(DIK_A) && mario->GetInHand()==NULL)
				{
					if (koopa->GetState() == KOOPA_STATE_CROUCH)
					{
						mario->SetInHand(e->obj);
						koopa->SetHolder(mario);
					}
					else
					{
						mario->SetInHand(NULL);
						koopa->SetHolder(NULL);
					}
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_GOOMBA||e->obj->GetObjectType() == OBJECT_TYPE_KOOPA)
			{
				if (e->ny<0)
				MiniJump(true);
			}
		}
	}
	for (UINT i = 0; i < mario->coEResult.size(); i++) delete  mario->coEResult[i];
	mario->coEResult.clear();
}
void PlayerLevel::MovingState(DWORD dt)
{	
	CGame* keyboard = CGame::GetInstance();
	
	if (keyboard->IsKeyDown(DIK_RIGHT) || keyboard->IsKeyDown(DIK_LEFT))
	{
		int key;
		
		if (keyboard->IsKeyDown(DIK_RIGHT))
			key = 1;
		else
			key= -1;
		if (mario->vx * key < 0 && mario->onGround == true)
		{
			if (mario->vx < 0) mario->isSkid = -1;
			else mario->isSkid = 1;
		}
		mario->SetState(MARIO_STATE_WALKING);
		mario->SetAcceleration(MARIO_WALKING_ACCELERATION * key);
		mario->SetDrag(MARIO_WALK_DRAG_FORCE);
		float maxspeed = MARIO_WALKING_SPEED;
		
		if (keyboard->IsKeyDown(DIK_A))
		{
			if (abs(mario->vx) == MARIO_RUNNING_SPEED)
				mario->SetState(MARIO_STATE_RUNNING);
			mario->SetAcceleration(MARIO_RUNNING_ACCELERATION * key);
			mario->SetDrag(MARIO_RUN_DRAG_FORCE);
			maxspeed = MARIO_RUNNING_SPEED;
		}

		if (mario->isSkid !=0)
		{
			mario->SetAcceleration(MARIO_SKID_ACCELERATION * key);
			mario->SetState(MARIO_STATE_SKID);
		}

		mario->vx += mario->GetAcceleration() * mario->dt;
		if (abs(mario->vx) > maxspeed)
		{
			if (abs(mario->vx) - maxspeed > MARIO_RUN_DRAG_FORCE * dt)
			{
				mario->vx -= MARIO_RUN_DRAG_FORCE * dt * mario->nx;
			}
			else
				mario->vx = maxspeed * key;
		}
		if (mario->vx < 0)mario->nx = -1;
		else mario->nx = 1;
		if (mario->vx *mario->isSkid <= 0) mario->isSkid = 0;
	}
	else //khong nhan gi 
	{
		if (abs(mario->vx) > mario->GetDrag()*dt )
		{
			mario->vx -= mario->GetDrag() * dt *mario->nx;
		}
		else
		{
			if(mario->GetState()!=MARIO_STATE_CROUCH )
				mario->SetState(MARIO_STATE_IDLE);
			mario->vx = 0;
		}
		mario->isSkid =0;
	}

}
void PlayerLevel::JumpingState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float jumpForce = MARIO_JUMP_FORCE;
	switch (mario->JumpState)
	{
	case MARIO_STATE_JUMP:
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpHigh)
		{
			jumpForce = MARIO_HIGH_JUMP_FORCE;
		}
		if (mario->vy > -jumpForce && mario->vy < 0 && mario->canJumpHigh )
		{
			mario->SetGravity(0);
			mario->vy -= MARIO_PUSH_FORCE * dt;
		}
		else
		{
			mario->SetGravity(MARIO_GRAVITY);
			//mario->vy -= jumpForce;
			mario->vy = - jumpForce;
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
		mario->SetGravity(0);
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpSuper)
		{
			jumpForce = MARIO_SUPER_JUMP_FORCE;
		}
		if (mario->vy > -jumpForce && mario->canJumpSuper && mario->vy < 0)
		{
			mario->vy -= MARIO_PUSH_FORCE * dt;
		}
		else
		{
			//mario->vy -= jumpForce;
			mario->vy = -jumpForce;

			mario->JumpState = MARIO_STATE_SUPER_FALL;
			mario->SetGravity(MARIO_GRAVITY);
		}
		break;
	case MARIO_STATE_SUPER_FALL:
	case MARIO_STATE_FALL:
		mario->SetGravity(MARIO_GRAVITY);
		if (mario->onGround == true)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
		}
		break;
	}
}
void PlayerLevel::CrouchState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float x, y;
	mario->GetPosition(x, y);
	y += collisionbox.y;
	if (keyboard->IsKeyDown(DIK_DOWN) && mario->JumpState == MARIO_STATE_JUMP_IDLE
		&& !keyboard->IsKeyDown(DIK_LEFT) && !keyboard->IsKeyDown(DIK_RIGHT) )
	{
		mario->SetState(MARIO_STATE_CROUCH);
		collisionbox.y = MARIO_CROUCH_BBOX_HEIGHT;
	}
	else
	{
		if(mario->GetState()!=MARIO_STATE_CROUCH)
		collisionbox.y = MARIO_BIG_BBOX_HEIGHT;
	}
	mario->SetPosition(x, y - collisionbox.y);
	//DebugOut(L"Mario moving state: %d \n", mario->GetState());
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
void PlayerLevel::MiniJump(bool isJump)
{
	CGame* keyboard = CGame::GetInstance();
	if ((keyboard->IsKeyDown(DIK_X) || isJump) && mario->onGround)
	{
		mario->vy = -MARIO_JUMP_FORCE;
		mario->canJumpHigh = false;
		mario->canJumpSuper = false;
		mario->JumpState = MARIO_STATE_JUMP;
	}
}
void PlayerLevel::OnKeyDown(int KeyCode)
{
	switch (KeyCode) {
	case DIK_S:
		if (mario->onGround && mario->GetPowerMeter() >= MARIO_POWER_METER_MAX)
		{
			mario->canJumpSuper = true;
			mario->JumpState = MARIO_STATE_SUPER_JUMP;
			mario->vy = -0.01;
		}
		else if (mario->onGround)
		{
			mario->canJumpHigh = true;
			mario->JumpState = MARIO_STATE_JUMP;
			mario->vy = -0.01;
		}
		break;
	}
}
void PlayerLevel::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_IDLE);
		break;
	case DIK_S:
		mario->canJumpHigh=false;
		break;
	}
}
