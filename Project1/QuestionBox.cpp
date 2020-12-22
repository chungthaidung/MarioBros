#include "QuestionBox.h"
#include "debug.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "CGame.h"
#include "CoinEff.h"
#include "SuperLeaf.h"
#include "CPlayScene.h"
#include "SwitchButton.h"
#include "define.h"
QuestionBox::QuestionBox(int obj_type,float y)
{
	y_start = y;
	SetReward(obj_type);
	state = QUESTION_BOX_REWARD;
	width = QUESTION_BOX_BBOX_WIDTH;
	height = QUESTION_BOX_BBOX_HEIGHT;
}

void QuestionBox::Render()
{
	int ani = QUESTION_BOX_ANI_REWARD;
	switch (state)
	{
	case QUESTION_BOX_REWARD:
		ani = QUESTION_BOX_ANI_REWARD;
		break;
	case QUESTION_BOX_EMPTY:
		ani = QUESTION_BOX_ANI_EMPTY;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}

void QuestionBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + QUESTION_BOX_BBOX_WIDTH;
	b = y + QUESTION_BOX_BBOX_HEIGHT;
}

void QuestionBox::Update(DWORD dt)
{
	RewardChecking();
	vy += gravity * dt;
	CGameObject::Update(dt);
	//DebugOut(L"{INFO] Start y %f.\n", y_start);
}

void QuestionBox::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void QuestionBox::FinalUpdate(DWORD dt)
{
	if (state == QUESTION_BOX_EMPTY) return;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (coEResult.size() == 0)
	{
		//x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;
	}

	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		/*if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
		{
			if (e->ny < 0 && state==QUESTION_BOX_REWARD)
			{
				SetState(QUESTION_BOX_BOUNC);
			}
		}*/
		 if ((e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState()==KOOPA_STATE_SHELL_RUNNING) || (e->obj->GetObjectType() == OBJECT_TYPE_TAIL))
		{
			if (e->nx!= 0 && state == QUESTION_BOX_REWARD)
			{
				SetState(QUESTION_BOX_BOUNC);
			}
		}
	}
	
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();
	Effect* eff = NULL;
	if (y < y_start - 40 && state == QUESTION_BOX_BOUNC)
	{
		vy = 0;
		y = y_start - 40;

	}
	else if ( y == y_start - 40 && state == QUESTION_BOX_BOUNC)
	{	
		SetState(QUESTION_BOX_EMPTY);
		if (reward->GetObjectType() != OBJECT_TYPE_COIN)
			CGame::GetInstance()->GetCurrentScene()->SpawnObject(reward);
		else 
		{
			eff = new CoinEff(); 
			eff->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		}
	}
}

void QuestionBox::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BOX_BOUNC:
		vy = -0.5;
		break;
	case QUESTION_BOX_EMPTY:
		vy = 0;
		y = y_start;
		reward->SetPosition(x, y);
		if (reward->GetObjectType() == OBJECT_TYPE_SUPER_LEAF) 
		{
			SuperLeaf* leaf = dynamic_cast<SuperLeaf*>(reward);
			leaf->SetXStart(x);
		}
		break;
	}
}

int QuestionBox::GetObjectType()
{
	return OBJECT_TYPE_QUESTION_BOX;
}

void QuestionBox::SetReward(int obj_type)
{
	switch (obj_type)
	{
	case OBJECT_TYPE_COIN:
		reward = new Coin();
		break;
	case OBJECT_TYPE_SUPER_MUSHROOM:
		reward = new SuperMushroom(y_start);
		reward->SetState(SUPER_MUSHROOM_STATE_UP);
		break;
	case OBJECT_TYPE_SUPER_LEAF:
		reward = new SuperLeaf(x,y_start);
		reward->SetState(SUPER_LEAF_STATE_UP);
		break;
	case OBJECT_TYPE_SWITCH_BUTTON:
		reward = new SwitchButton();
		reward->SetState(SWITCH_BUTTON_STATE_UP);
		break;
	}
}

void QuestionBox::RewardChecking()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
//	DebugOut(L"Mario level: %d\n ", mario->GetLevel());
	if (mario->GetLevel()<MARIO_LEVEL_BIG)
	{
		if (reward->GetObjectType() == OBJECT_TYPE_SUPER_LEAF)
			SetReward(OBJECT_TYPE_SUPER_MUSHROOM);
	}
}

void QuestionBox::SetRewardnx(int nx_r)
{
	if(reward->GetObjectType()==OBJECT_TYPE_SUPER_MUSHROOM)
		reward->Setnx(nx_r);
}
