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
#include "CPlayScene.h"
#include "CheckPoint.h"
#include "MarioDieEff.h"
CMario::CMario(float x, float y) : CGameObject()
{
	level_p = new SmallMario(this); 
	JumpState = MARIO_STATE_JUMP_IDLE;
	untouchable = false;
	inHand = NULL;
	SetState(MARIO_STATE_IDLE);
	gravity = MARIO_GRAVITY;
	renderOrder = 0;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	endgame_reward.clear();

}

void CMario::Update(DWORD dt)
{
	LockControlUpdate(dt);

	level_p->Update(dt);
	if (x< 0) x = 0;

}

void CMario::LockControlUpdate(DWORD dt)
{
	if (lockcontrol == false) return;
	if (onGround == true)
	{
		SetState(MARIO_STATE_WALKING);
		gravity = 0;
		vx = MARIO_WALKING_SPEED;
		nx = 1;
	}
}

void CMario::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	level_p->CollisionUpdate(dt, colliable_objects);
}

void CMario::FinalUpdate(DWORD dt)
{
	level_p->FinalUpdate(dt);
	//DebugOut(L"Power Meter: %f\n", powerM);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (y > scene->GetBoundary().bottom && state != MARIO_STATE_DIE)
	{
		SetState(MARIO_STATE_DIE);
		SetLevel(MARIO_LEVEL_SMALL);
	}
	else
	if (state == MARIO_STATE_DIE && GetTickCount() - dietime > 2000)
	{
		CGame::GetInstance()->SetMarioLife(-1);
		CGame::GetInstance()->SwitchScene(WORLD_MAP);
	}
}

void CMario::Render()
{
	level_p->Render();
}

bool CMario::GetUntouchable()
{
	return untouchable;
}

DWORD CMario::GetUntouchableStart()
{
	return untouchable_start;
}

bool CMario::GetLockControl()
{
	return lockcontrol;
}

void CMario::SetUntouchable(bool a)
{
	untouchable = a;
}

void CMario::SetUntouchableStart(DWORD a)
{
	untouchable_start = a;
}

void CMario::SetLockControl(bool a)
{
	lockcontrol = a;
}

void CMario::SetInHand(CGameObject* obj)
{
	inHand = obj;
}

void CMario::LevelUp(CGameObject* obj)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	switch (obj->GetObjectType())
	{
	case OBJECT_TYPE_SUPER_MUSHROOM:
		if (level_p->GetPlayerLevel() != MARIO_LEVEL_BIG)
		{
			scene->SetDelayTime(500);
			SetLevel(MARIO_LEVEL_BIG);
			if(JumpState==MARIO_STATE_JUMP_IDLE)
				SetState(MARIO_STATE_IDLE);
		}
		break;
	case OBJECT_TYPE_SUPER_LEAF:
		if (level_p->GetPlayerLevel() != MARIO_LEVEL_RACOON)
		{
			scene->SetDelayTime(500);
			SetLevel(MARIO_LEVEL_RACOON);
		}
		break;
	}
}

void CMario::LevelDown()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	StartUntouchable();
	switch (level_p->GetPlayerLevel())
	{
	case MARIO_LEVEL_SMALL:
		//SetLevel(MARIO_LEVEL_SMALL);
		SetState(MARIO_STATE_DIE);
		scene->SetDelayTime(1000);
		break;
	case MARIO_LEVEL_BIG:
		SetLevel(MARIO_LEVEL_SMALL);
		scene->SetDelayTime(500);
		break;
	case MARIO_LEVEL_RACOON:
		if (AttackState == MARIO_STATE_ATTACK_START)
		{
			RacoonMario* racoon = (RacoonMario*)level_p;
			racoon->GetMarioWeapon()->SetActive(false);
		}
		SetLevel(MARIO_LEVEL_BIG);	
		scene->SetDelayTime(500);
		break;
	case MARIO_LEVEL_FIRE:
		SetLevel(MARIO_LEVEL_BIG);
		scene->SetDelayTime(500);
		break;
	}
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
	if (state == MARIO_STATE_DIE)
	{
		dietime = GetTickCount();
		MarioDieEff* dieeff = new MarioDieEff(D3DXVECTOR2(x, y));
		CGame::GetInstance()->GetCurrentScene()->AddEffect(dieeff);
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	level_p->GetBoundingBox(left,top,right,bottom);
}

bool CMario::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (untouchable == true && obj->isEnemy == true) {
		//DebugOut(L"SKIP\n");
		return true;
	}
	if (obj->GetObjectType() == OBJECT_TYPE_GHOST && (direction.y > 0 || direction.x != 0))
		return true;
	if (obj->GetObjectType() == OBJECT_TYPE_COIN )
		return true;
	if (obj->GetState() == BRICK_COIN && obj->GetObjectType() == OBJECT_TYPE_BRICK) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_END_GAME_REWARD) return true;
	//if (GetUntouchable() && obj->isEnemy) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_CHECKPOINT)
	{
		CheckPoint* checkpoint = dynamic_cast<CheckPoint*>(obj);
		if (checkpoint->GetDirection().x != 0)
		{
			if (direction.x != checkpoint->GetDirection().x) return true;
		}
		else if (checkpoint->GetDirection().y != 0)
		{
			if (direction.y != checkpoint->GetDirection().y) return true;
		}
	}
	return false;
}

RECT CMario::GetBoundingBox()
{
	RECT a;
	float left, top, right, bottom;
	level_p->GetBoundingBox(left, top, right, bottom);
	a.left = long(left);
	a.top = long(top);
	a.right = long(right);
	a.bottom = long(bottom);
	return a;
}

int CMario::GetObjectType()
{
	return OBJECT_TYPE_MARIO;
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	//SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(x, start_y);
	SetSpeed(0, 0);
}
void CMario::SetLevel(int level)
{
	y += level_p->GetCollisionBox().y;
	//if (AttackState != MARIO_STATE_ATTACK_START)
	//{
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
	//}
	y -= level_p->GetCollisionBox().y;
}
void CMario::StartUntouchable()
{
	DebugOut(L"TURN ON UNTOUCHABLE \n");
	untouchable = true; 
	untouchable_start = GetTickCount();
}
void CMario::StopUntouchable()
{
	DebugOut(L"TURN OFF UNTOUCHABLE \n");
	untouchable=false;
	untouchable_start = 0;
}
void CMario::OnKeyDown(int KeyCode)
{
	if (lockcontrol == true) return;
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
	if (lockcontrol == true) return;
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