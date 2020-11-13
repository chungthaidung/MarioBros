#include "RacoonMario.h"
#include "CGame.h"
#include "debug.h"
RacoonMario::RacoonMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_RACOON_BBOX_WIDTH;
	collisionbox.y = MARIO_RACOON_BBOX_HEIGHT;
	tail = new MarioTail(mario);
	tail->SetActive(false);

}
void RacoonMario::Update(DWORD dt)
{
	//if (tail->GetActive()) tail->Update(dt);

	PlayerLevel::Update(dt);

}
void RacoonMario::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	//if (tail->GetActive()) tail->CollisionUpdate(dt, colliable_objects);
	PlayerLevel::CollisionUpdate(dt,colliable_objects);
}
void RacoonMario::FinalUpdate(DWORD dt)
{
	//if (tail->GetActive()) tail->FinalUpdate(dt);
	PlayerLevel::FinalUpdate(dt);
}
int RacoonMario::GetPlayerLevel()
{
	return 3;
}
void RacoonMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void RacoonMario::Render()
{
	int ani = MARIO_ANI_RACOON_IDLE;
	if (mario->GetState() == MARIO_STATE_CROUCH)
	{
		ani = MARIO_ANI_RACOON_CROUCH;
	}
	else if (mario->AttackState == MARIO_STATE_ATTACK_START)
	{
		ani = MARIO_ANI_RACOON_SPIN;
	}
	else if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_RACOON_JUMP;
			break;
		case MARIO_STATE_FALL:
			ani = MARIO_ANI_RACOON_FALL;
			break;
		case MARIO_STATE_SUPER_JUMP:
			ani = MARIO_ANI_RACOON_SUPER_JUMP;
			break;
		case MARIO_STATE_SUPER_FALL:
			ani = MARIO_ANI_RACOON_SUPER_FALL;
			break;
		case MARIO_STATE_FLY:
			ani = MARIO_ANI_RACOON_FLY;
			break;
		case MARIO_STATE_FLOAT:
			ani = MARIO_ANI_RACOON_FLOAT;
			break;
		}
	}
	else {
		switch (mario->GetState())
		{
		case MARIO_STATE_IDLE:
			ani = MARIO_ANI_RACOON_IDLE;
			break;
		case MARIO_STATE_WALKING:
			ani = MARIO_ANI_RACOON_WALKING;
			break;
		case MARIO_STATE_RUNNING:
			ani = MARIO_ANI_RACOON_RUNNING;
			break;
		case MARIO_STATE_JUMP:
			ani = MARIO_ANI_RACOON_JUMP;
			break;
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_RACOON_SKID;
			break;
		case MARIO_STATE_CROUCH:
			ani = MARIO_ANI_RACOON_CROUCH;
			break;
		}
	}
		
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	//if (tail->GetActive()) tail->Render();
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
void RacoonMario::AttackState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_Z)) {
		if (mario->AttackState != MARIO_STATE_ATTACK_START) {
			mario->AttackState = MARIO_STATE_ATTACK_START;
			attacktime = GetTickCount();
			tail->SetActive(true);
			CGame::GetInstance()->GetCurrentScene()->SpawnObject(tail);
			//DebugOut(L"5555 \n");
		}
	}
	switch (mario->AttackState)
	{
	case MARIO_STATE_ATTACK_START:
		if (GetTickCount() - attacktime >= 500) {
			mario->AttackState = MARIO_STATE_ATTACK_END;
		}
		break;
	case MARIO_STATE_ATTACK_END:
		tail->SetActive(false);
		tail->isRemove = true;
		break;
	}

}
void RacoonMario::JumpingState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float jumpForce = MARIO_JUMP_FORCE;
	mario->SetyPush(MARIO_PUSH_FORCE);
	switch (mario->JumpState)
	{
	case MARIO_STATE_JUMP:
		mario->SetGravity(0);
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpHigh)
		{
			jumpForce = MARIO_HIGH_JUMP_FORCE;
		}

		if (mario->vy > -jumpForce && mario->canJumpHigh)
		{
			mario->vy -= mario->GetyPush() * dt;
		}
		else
		{
			mario->vy = -jumpForce;
			mario->JumpState = MARIO_STATE_HIGH_JUMP;
			mario->SetGravity(MARIO_GRAVITY);
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
		if (mario->vy > -jumpForce && mario->canJumpSuper)
		{
			mario->vy -= mario->GetyPush() * dt;
		}
		else
		{
			mario->vy = -jumpForce;
			mario->JumpState = MARIO_STATE_SUPER_FALL;
			mario->SetGravity(MARIO_GRAVITY);
		}
		break;
	case MARIO_STATE_FLOAT:
		if (keyboard->IsKeyDown(DIK_X))
			mario->vy -= MARIO_FLOAT * dt;
		else mario->JumpState = MARIO_STATE_FALL;
		if (mario->onGround == true)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
		}
		break;
	case MARIO_STATE_FLY:
		if (GetTickCount() - flytime < 4000) {
			if (keyboard->IsKeyDown(DIK_X))
			{
				if (mario->vy > 0) mario->vy = 0;
				mario->SetGravity(0);
				mario->vy = -MARIO_FLY_FORCE;
			}
			else mario->SetGravity(MARIO_GRAVITY);

		}
		else
		{
			mario->SetGravity(MARIO_GRAVITY);
			mario->JumpState = MARIO_STATE_FLOAT;
		}
		if (mario->onGround == true)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
		}
		break;
	case MARIO_STATE_SUPER_FALL:
	case MARIO_STATE_FALL:
		if (mario->onGround)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
		}
		break;
	}
	
}
void RacoonMario::PowerMeterUpdate(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float power = mario->GetPowerMeter();
	if ((abs(mario->vx) > MARIO_WALKING_SPEED||keyboard->IsKeyDown(DIK_Z))&& mario->onGround)
	{
		if (power < 0) power = 0;
		power += MARIO_POWER_METER_UP * dt;
		if (power > MARIO_POWER_METER_MAX + 1)
			power = MARIO_POWER_METER_MAX;
	}
	else 
	{

		if (mario->GetPowerMeter() > 0 && mario->JumpState==MARIO_STATE_JUMP_IDLE) {
			power -= MARIO_POWER_METER_DOWN * dt;
			if (power < 0)
				power = 0;
		}
	}
	mario->SetPowerMeter(power);
}
void RacoonMario::MiniJump(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_X) && mario->onGround)
	{
		mario->vy = -MARIO_JUMP_FORCE;
		mario->canJumpHigh = false;
		mario->canJumpSuper = false;
		mario->JumpState = MARIO_STATE_JUMP;
	}
	else if (keyboard->IsKeyDown(DIK_X) )
	{
		if (mario->JumpState == MARIO_STATE_FALL)
		{
			mario->JumpState = MARIO_STATE_FLOAT;
		}
		else if (mario->JumpState == MARIO_STATE_SUPER_FALL || mario->JumpState == MARIO_STATE_SUPER_JUMP)
		{
			flytime = GetTickCount();
			mario->vy = 0;
			mario->JumpState = MARIO_STATE_FLY;

		}
	}
}
void RacoonMario::OnKeyDown(int KeyCode)
{
	DWORD dt = CGame::DeltaTime;
	switch (KeyCode)
	{
	case DIK_A:
		mario->AttackState = MARIO_STATE_ATTACK_START;
		attacktime = GetTickCount();
		break;
	}
}
