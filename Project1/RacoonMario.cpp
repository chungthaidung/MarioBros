#include "RacoonMario.h"
#include "CGame.h"
#include "debug.h"
RacoonMario::RacoonMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_RACOON_BBOX_WIDTH;
	collisionbox.y = MARIO_RACOON_BBOX_HEIGHT;
	tail = new MarioTail(mario);
	tail->SetActive(false);
	tail->canDelete = false;
}
int RacoonMario::GetPlayerLevel()
{
	return 3;
}
MarioTail* RacoonMario::GetMarioWeapon()
{
	return tail;
}
void RacoonMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void RacoonMario::Render()
{
	int alpha = 255;
	int f = 1;
	int ani = MARIO_ANI_RACOON_IDLE;
	if (mario->GetUntouchable() == true)
	{
		int dt = CGame::GetInstance()->DeltaTime;
		if (dt % 2 == 0)
		{
			alpha = 128;
		}
		else {
			alpha = 255;
		}
	}
	if (mario->GetState() == MARIO_STATE_CROUCH)
	{
		ani = MARIO_ANI_RACOON_CROUCH;
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
		CAnimations::GetInstance()->Get(ani)->Render(mario->x-cx, mario->y-cy, 1, mario->nx * f,1, alpha);
		mario->RenderBoundingBox();
	}
	else if (mario->AttackState == MARIO_STATE_ATTACK_START)
	{
		ani = MARIO_ANI_RACOON_SPIN;
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
		CAnimations::GetInstance()->Get(ani)->Render(mario->x-cx, mario->y-cy,attacktime,MARIO_ATTACK_TIME, 1, mario->nx*f,1, alpha);
		mario->RenderBoundingBox();
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
		if (mario->GetInHand() != NULL)
		{
			ani = MARIO_ANI_RACOON_HOLD_FALL;
		}
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	
		CAnimations::GetInstance()->Get(ani)->Render(mario->x-cx, mario->y-cy, 1, mario->nx*f,1, alpha);
		mario->RenderBoundingBox();
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
			f = -1;
			break;
		}
		if (mario->GetInHand() != NULL && mario->GetState() == MARIO_STATE_IDLE)
			ani = MARIO_ANI_RACOON_HOLD_IDLE;
		else if (mario->GetInHand() != NULL)
			ani = MARIO_ANI_RACOON_HOLD;
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
		CAnimations::GetInstance()->Get(ani)->Render(mario->x-cx, mario->y-cy, 1, mario->nx*f,1, alpha);
		mario->RenderBoundingBox();
	}
		
	//if (mario->untouchable) alpha = 128;
	
}
void RacoonMario::AttackState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_Z) && mario->GetState()!=MARIO_STATE_CROUCH) {
		if (mario->AttackState != MARIO_STATE_ATTACK_START) {
			mario->AttackState = MARIO_STATE_ATTACK_START;
			attacktime = GetTickCount();
			tail->SetActive(true);
			CGame::GetInstance()->GetCurrentScene()->SpawnObjectWithoutGrid(tail);
			//DebugOut(L"5555 \n");
		}
	}
	switch (mario->AttackState)
	{
	case MARIO_STATE_ATTACK_START:
		if (GetTickCount() - attacktime >= MARIO_ATTACK_TIME) {
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
	switch (mario->JumpState)
	{
	case MARIO_STATE_JUMP:
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpHigh)
		{
			jumpForce = MARIO_HIGH_JUMP_FORCE;
		}

		if (mario->vy > -jumpForce && mario->canJumpHigh && mario->vy < 0)
		{
			mario->SetGravity(0);
			mario->vy -= MARIO_PUSH_FORCE;
		}
		else
		{
			mario->vy = -jumpForce;
			//mario->vy -= jumpForce;
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
		
		if (keyboard->IsKeyDown(DIK_S) && mario->canJumpSuper )
		{
			jumpForce = MARIO_SUPER_JUMP_FORCE;
		}
		if (mario->vy > -jumpForce && mario->canJumpSuper && mario->vy < 0)
		{
			mario->vy -= MARIO_PUSH_FORCE;
			mario->SetGravity(0);
		}
		else
		{
			mario->vy = -jumpForce;
			//mario->vy -= jumpForce;
			mario->JumpState = MARIO_STATE_SUPER_FALL;
			mario->SetGravity(MARIO_GRAVITY);
		}
		break;
	case MARIO_STATE_FLOAT:
		if (keyboard->IsKeyDown(DIK_X) || flyflag>0)
		{
			/*if (flyflag) mario->vy += 2.2*MARIO_FLOAT * dt;
			else
			{*/
				mario->SetGravity(0);
				mario->vy += MARIO_FLOAT * dt;
			//}
			//DebugOut(L"mario->vy: %f\n", mario->vy);
			flyflag -= dt;
		}
		else mario->JumpState = MARIO_STATE_FALL;
		if (mario->onGround == true)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
			mario->SetGravity(MARIO_GRAVITY);
		}
		break;
	case MARIO_STATE_FLY:
		CGame::GetInstance()->GetCurrentScene()->GetCamera()->SetLockCam(true);
		if ( flytime < 4000) { //GetTickCount() - 
			if (keyboard->IsKeyDown(DIK_X) || flyflag>0)
			{
				if (mario->vy > 0) mario->vy = 0;
				mario->SetGravity(0);
				//if (flyflag) mario->vy = -0.42f; // nhap S lien tuc
				 mario->vy = -MARIO_FLY_FORCE;
			}
			else mario->SetGravity(MARIO_GRAVITY);
			flyflag -= dt;
		}
		else
		{
			mario->SetPowerMeter(0);
			mario->SetGravity(MARIO_GRAVITY);
			mario->JumpState = MARIO_STATE_FLOAT;
		}
		if (mario->onGround == true)
		{
			mario->JumpState = MARIO_STATE_JUMP_IDLE;
			mario->SetGravity(MARIO_GRAVITY);
		}
		flytime += dt;
		//DebugOut(L"FLY time: %d \n",flytime);
		break;
	case MARIO_STATE_SUPER_FALL:
	case MARIO_STATE_FALL:
		mario->SetGravity(MARIO_GRAVITY);
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
	if ((abs(mario->vx) > MARIO_WALKING_SPEED)&& mario->onGround)
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
void RacoonMario::MiniJump(bool isJump)
{
	CGame* keyboard = CGame::GetInstance();
	DWORD dt = CGame::DeltaTime;
	if ((keyboard->IsKeyDown(DIK_X)||isJump) && mario->onGround)
	{
		mario->vy = -MARIO_JUMP_FORCE;
		mario->canJumpHigh = false;
		mario->canJumpSuper = false;
		mario->JumpState = MARIO_STATE_JUMP;
	}
	else if (keyboard->IsKeyDown(DIK_X) || flyflag>0 )
	{
		if (mario->JumpState == MARIO_STATE_FALL)
		{
			mario->JumpState = MARIO_STATE_FLOAT;
			mario->vy=MARIO_GRAVITY*dt;
		}
		else if (mario->JumpState == MARIO_STATE_SUPER_FALL || mario->JumpState == MARIO_STATE_SUPER_JUMP)
		{
			flytime = 0;
			mario->vy = 0;
			mario->JumpState = MARIO_STATE_FLY;
		}
	}
}
void RacoonMario::OnKeyDown(int KeyCode)
{
	//PlayerLevel::OnKeyDown(KeyCode);
	switch (KeyCode)
	{
	case DIK_A:
		mario->AttackState = MARIO_STATE_ATTACK_START;
		tail->SetActive(true);
		CGame::GetInstance()->GetCurrentScene()->SpawnObjectWithoutGrid(tail);
		attacktime = GetTickCount();
		break;
	case DIK_S:
		if (mario->onGround && mario->GetPowerMeter() >= MARIO_POWER_METER_MAX && mario->JumpState!= MARIO_STATE_SUPER_JUMP)
		{
			mario->canJumpSuper = true;
			mario->JumpState = MARIO_STATE_SUPER_JUMP;
			mario->vy = -0.4;
		}
		else if (mario->onGround)
		{
			mario->canJumpHigh = true;
			mario->JumpState = MARIO_STATE_JUMP;
			mario->vy = -0.4;
		}
		else if (mario->JumpState == MARIO_STATE_SUPER_JUMP || mario->JumpState == MARIO_STATE_FALL ||
			mario->JumpState == MARIO_STATE_SUPER_FALL || mario->JumpState == MARIO_STATE_FLY || mario->JumpState == MARIO_STATE_FLOAT)
			flyflag = 200;
		break;
	}
}
void RacoonMario::OnKeyUp(int KeyCode)
{
	PlayerLevel::OnKeyUp(KeyCode);
	//switch (KeyCode)
	//{
	//case DIK_S:
	//	if (flyflag == true) {
	//		flyflag = false;
	//		//mario->vy = 0;
	//	}
	//	break;
	//}
}
RacoonMario::~RacoonMario()
{
	CGame::GetInstance()->GetCurrentScene()->DespawnObject(tail);
}
