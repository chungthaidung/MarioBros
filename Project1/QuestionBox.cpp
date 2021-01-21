#include "QuestionBox.h"
#include "debug.h"
#include "Coin.h"
#include "SuperMushroom.h"
#include "CGame.h"
#include "CoinEff.h"
#include "SuperLeaf.h"
#include "CPlayScene.h"
#include "SwitchButton.h"
#include "PointsEff.h"
#include "define.h"
#include "UpMushroom.h"
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
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
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
	y += dy;

	if (coEResult.size() == 0)
	{
		//x += dx;

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
			CGame::GetInstance()->SetPoints(100);
			eff = new CoinEff();
			eff->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		}
	}
	RewardChecking();

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
	/*	if (reward->GetObjectType() == OBJECT_TYPE_SUPER_LEAF) 
		{
			SuperLeaf* leaf = dynamic_cast<SuperLeaf*>(reward);
			leaf->SetXStart(x);
		}*/
		break;
	}
}

int QuestionBox::GetObjectType()
{
	return OBJECT_TYPE_QUESTION_BOX;
}

bool QuestionBox::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
	{
		CMario* mario = dynamic_cast<CMario*>(obj);
		if (mario->GetUntouchable() == true) return true;
	}
	return false;
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
	case OBJECT_TYPE_UP_MUSHROOM:
		reward = new UpMushroom(y_start);
		reward->SetState(UP_MUSHROOM_STATE_UP);
		break;
	}
}

void QuestionBox::RewardChecking()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	if (reward->GetObjectType() == OBJECT_TYPE_SUPER_LEAF)
	{
		if (mario->GetLevel() < MARIO_LEVEL_BIG)
		{
			SetReward(OBJECT_TYPE_SUPER_MUSHROOM);
		}
		else SetReward(OBJECT_TYPE_SUPER_LEAF);
	}
	
	
}

void QuestionBox::SetRewardnx(int nx_r)
{
	if(reward->GetObjectType()==OBJECT_TYPE_SUPER_MUSHROOM)
		reward->Setnx(nx_r);
}
