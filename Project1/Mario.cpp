#include <algorithm>
#include "debug.h"
#include "BigMario.h"
#include "Mario.h"
#include "CGame.h"
#include "SmallMario.h"
#include "CGameObject.h"
#include "GhostObject.h"
#include "RacoonMario.h"
#include "FireMario.h"
CMario::CMario(float x, float y) : CGameObject()
{
	level_p = new SmallMario(this); 
	level = MARIO_LEVEL_SMALL;//hardcode
	JumpState = MARIO_STATE_JUMP_IDLE;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	gravity = MARIO_GRAVITY;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	level_p->Update(dt,coObjects);
	if (x< 0) x = 0;
}

void CMario::Render()
{
	level_p->Render();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	level_p->SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	level_p->GetBoundingBox(left,top,right,bottom);
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(x, start_y);
	SetSpeed(0, 0);
}
void CMario::SetLevel(int level)
{
	y += level_p->GetCollisionBox().y;
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		level_p = new SmallMario(this);
		
		break;
	case MARIO_LEVEL_BIG:
		level_p = new BigMario(this);
		break;
	case MARIO_LEVEL_RACOON:
		level_p = new RacoonMario(this);
		break;
	case MARIO_LEVEL_FIRE:
		level_p = new FireMario(this);
		break;
	}
	y -= level_p->GetCollisionBox().y;
}
void CMario::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	level_p->OnKeyDown(KeyCode);
	switch (KeyCode)
	{
	case DIK_S:
		if (onGround && powerM >= MARIO_POWER_METER_MAX)
		{
			canJumpSuper = true;
			JumpState = MARIO_STATE_SUPER_JUMP;
		}
		else if (onGround)
		{
			canJumpHigh = true;
			JumpState = MARIO_STATE_JUMP;
		}
		break;
	case DIK_R:
		Reset();
		break;
	case DIK_1:
		SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		SetLevel(MARIO_LEVEL_FIRE);
		break;
	}
}
void CMario::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	/*switch (KeyCode)
	{
	case DIK_A:
		if (KeyCode == DIK_RIGHT)
			SetState(MARIO_STATE_WALKING_RIGHT);
		else if (KeyCode == DIK_LEFT)
			SetState(MARIO_STATE_WALKING_LEFT);
		else
			SetState(MARIO_STATE_IDLE);
		break;
	case DIK_LEFT:
	case DIK_RIGHT:
		SetState(MARIO_STATE_IDLE);
		break;
	}*/
}