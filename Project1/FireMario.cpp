#include "FireMario.h"
#include "CGame.h"
#include "debug.h"
FireMario::FireMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_FIRE_BBOX_WIDTH;
	collisionbox.y = MARIO_FIRE_BBOX_HEIGHT;
	
	for (int i = 0; i < 2; i++)
	{
		MarioFireBall* ball = new MarioFireBall(mario);
		ball->SetActive(false);
		fireballs.push_back(ball);
	}
}
void FireMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsActive() == true)	fireballs.at(ballnumber)->Update(dt, coObjects);
	PlayerLevel::Update(dt, coObjects);
	
}
void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void FireMario::Render()
{
	
	int ani = MARIO_ANI_FIRE_IDLE;
	if (mario->AttackState == MARIO_STATE_ATTACK_START)
	{
		ani = MARIO_ANI_FIRE_THROW;

	}
	else if (mario->isCrouch == true)
	{
		ani = MARIO_ANI_FIRE_CROUCH;
	}
	else if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_FIRE_JUMP;
			break;
		case MARIO_STATE_FALL:
			ani = MARIO_ANI_FIRE_FALL;
			break;
		case MARIO_STATE_SUPER_FALL:
		case MARIO_STATE_SUPER_JUMP:
			ani = MARIO_ANI_FIRE_SUPER_JUMP;
			break;
		}
	}
	else {
		switch (mario->GetState())
		{
		case MARIO_STATE_IDLE:
			ani = MARIO_ANI_FIRE_IDLE;
			break;
		case MARIO_STATE_WALKING:
			ani = MARIO_ANI_FIRE_WALKING;
			break;
		case MARIO_STATE_RUNNING:
			ani = MARIO_ANI_FIRE_RUNNING;
			break;
		case MARIO_STATE_JUMP:
			ani = MARIO_ANI_FIRE_JUMP;
			break;
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_FIRE_SKID;
			break;
		}
	}

	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
	if (IsActive() == true)
		fireballs.at(ballnumber) ->Render();
}
void FireMario::CrouchState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float x, y;
	mario->GetPosition(x, y);
	y += collisionbox.y;
	if (mario->state == MARIO_STATE_IDLE && keyboard->IsKeyDown(DIK_DOWN))
	{
		mario->isCrouch = true;
		collisionbox.y = MARIO_CROUCH_BBOX_HEIGHT;
	}
	else
	{
		mario->isCrouch = false;
		collisionbox.y = MARIO_FIRE_BBOX_HEIGHT;
	}
	mario->SetPosition(x, y - collisionbox.y);
}
void FireMario::AttackState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	switch (mario->AttackState)
	{
	case MARIO_STATE_ATTACK_START:
		DWORD now = GetTickCount();
		if (now - attacktime <250)
		{ 
			if (now - attacktime > 100 && !IsActive()) {
				fireballs.at(ballnumber)->SetActive(true);
				fireballs.at(ballnumber)->Setnx(mario->nx);
				if (mario->nx>0) fireballs.at(ballnumber)->Reset(mario->x+collisionbox.x,mario->y);
				else fireballs.at(ballnumber)->Reset(mario->x - MARIO_FIRE_BALL_BBOX_WIDTH, mario->y);
			}
		}
		else mario->AttackState = MARIO_STATE_ATTACK_END;
		break;
	}
	DebugOut(L"Is Active %d ball num %d \n", fireballs.at(ballnumber)->GetActive(),ballnumber);
}
void FireMario::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_Z:
		if (IsActive() == false)
		{
			mario->AttackState = MARIO_STATE_ATTACK_START;
			attacktime = GetTickCount();
		}else mario->AttackState = MARIO_STATE_ATTACK_END;
		break;
	}
}
bool FireMario::IsActive()
{
	
	for (int i = 0; i < 2; i++)
	{
		if (fireballs.at(i)->GetActive()==false)
		{
			ballnumber = i;
			return false;
		}
	}
	return true;
}
void FireMario::AttackStart(DWORD dt)
{
	for (int i = 0; i < 2; i++)
	{
		if (fireballs.at(i)->GetActive())
		{
			if (mario->nx > 0)
				fireballs.at(i)->SetPosition(mario->x + collisionbox.x, mario->y);
			else
				fireballs.at(i)->SetPosition(mario->x - MARIO_FIRE_BALL_BBOX_WIDTH, mario->y);
			fireballs.at(i)->Setnx(mario->nx);
		}
	}
}