#include <algorithm>
#include "debug.h"
#include "BigMario.h"
#include "Mario.h"
#include "CGame.h"
#include "SmallMario.h"
#include "CGameObject.h"
#include "GhostObject.h"
#include "Koopa.h"
#include "RacoonMario.h"
#include "FireMario.h"
CMario::CMario(float x, float y) : CGameObject()
{
	level_p = new SmallMario(this); 
	//level = MARIO_LEVEL_SMALL;//hardcode
	JumpState = MARIO_STATE_JUMP_IDLE;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	gravity = MARIO_GRAVITY;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt)
{
	level_p->Update(dt);
	if (x< 0) x = 0;

}

void CMario::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	level_p->CollisionUpdate(dt, colliable_objects);
}

void CMario::FinalUpdate(DWORD dt)
{
	level_p->FinalUpdate(dt);
}

void CMario::Render()
{
	level_p->Render();
}

void CMario::SetInHand(CGameObject* obj)
{
	inHand = obj;
}



CGameObject* CMario::GetInHand()
{
	return inHand;
}

D3DXVECTOR2 CMario::GetCollisionBox()
{
	return level_p->GetCollisionBox();
}

int CMario::GetLevel()
{
	return level_p->GetPlayerLevel();
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

int CMario::GetObjectType()
{
	return 0;
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
	if (AttackState != MARIO_STATE_ATTACK_START)
	{
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
	}
	y -= level_p->GetCollisionBox().y;
}
void CMario::StartUntouchable()
{
	untouchable = 1; 
	untouchable_start = GetTickCount64();
}
void CMario::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	level_p->OnKeyDown(KeyCode);
	switch (KeyCode)
	{
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
	level_p->OnKeyUp(KeyCode);
	switch (KeyCode)
	{
	case DIK_A:
		if (inHand != NULL)
		{
			if (inHand->GetObjectType() == OBJECT_TYPE_KOOPA)
			{
				Koopa* koopa = dynamic_cast<Koopa*>(inHand);
				if (koopa->GetState() == KOOPA_STATE_CROUCH)
				{
					if (nx > 0)
					{
						koopa->SetPosition(x + level_p->GetCollisionBox().x + 1, y + level_p->GetCollisionBox().y - koopa->GetCollisionBox().y);
					}
					else
					{
						koopa->SetPosition(x - koopa->GetCollisionBox().x - 1, y + level_p->GetCollisionBox().y - koopa->GetCollisionBox().y);
					}
					koopa->SetHolder(NULL);
					inHand = NULL;
				}
				else 
				{
					koopa->SetHolder(NULL);
					inHand = NULL;
				}
			}
		}
		else
		{
			inHand = NULL;
		}
		break;
	}
}