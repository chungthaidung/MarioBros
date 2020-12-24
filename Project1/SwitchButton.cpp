#include "SwitchButton.h"
#include "Brick.h"
#include "debug.h"
#include "CGame.h"
SwitchButton::SwitchButton():CGameObject()
{

	vx = 0;
	vy = 0;
	collisionbox.x = SWITCH_BUTTON_BBOX_WIDTH;
	collisionbox.y = SWITCH_BUTTON_BBOX_HEIGHT;
}

void SwitchButton::Update(DWORD dt)
{
	
	CGameObject::Update(dt);
}

void SwitchButton::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == SWITCH_BUTTON_STATE_UP){
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetObjectType() == OBJECT_TYPE_BRICK && coObjects->at(i)->GetState()== BRICK_BREAKABLE)
			{
				bricks.push_back(coObjects->at(i));
			}
		}
	}
	else if (state == SWITCH_BUTTON_STATE_DOWN)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetObjectType() == OBJECT_TYPE_BRICK && coObjects->at(i)->GetState() == BRICK_COIN)
			{
				bricks.push_back(coObjects->at(i));
			}
		}
	}
	CalcPotentialCollisions(coObjects, coEResult);
}

void SwitchButton::FinalUpdate(DWORD dt)
{
	if (state == SWITCH_BUTTON_STATE_DOWN && GetTickCount() - time > 6100) return;
	//DebugOut(L"BRICK SIZE: %d\n", bricks.size());

	if (GetTickCount() - time > 6000&& bricks.size()>0)
	{
		for (int i = 0; i < bricks.size(); i++)
		{
			if (bricks[i] == NULL) continue;
			Brick* br = dynamic_cast<Brick*>(bricks[i]);
			br->DespawnCoin();
		}
	}
	if (state == SWITCH_BUTTON_STATE_DOWN) { 
		bricks.clear();
		return; }

	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();

	if (coEResult.size() == 0)
	{
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO && e->ny>0 && state==SWITCH_BUTTON_STATE_UP)
			{
				SetState(SWITCH_BUTTON_STATE_DOWN);
			}
		}
	}
	
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();

	if (state == SWITCH_BUTTON_STATE_UP){
	//for (UINT i = 0; i < bricks.size(); i++) delete bricks[i];
	bricks.clear();
	}
//	RemoveBricks();
}

void SwitchButton::Render()
{
	int ani = SWITCH_BUTTON_ANI_UP;
	if (state == SWITCH_BUTTON_STATE_DOWN) 
		ani = SWITCH_BUTTON_ANI_DOWN;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}

void SwitchButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + collisionbox.x;
	b = y + collisionbox.y;
}

void SwitchButton::SetState(int state)
{
	y += collisionbox.y;
	CGameObject::SetState(state);
	switch (state)
	{
	case SWITCH_BUTTON_STATE_UP:
		break;
	case SWITCH_BUTTON_STATE_DOWN:
		collisionbox.y = 21;
		time = GetTickCount();
		//DebugOut(L"Bricks size: %d \n", bricks.size());
		for (int i = 0; i < bricks.size(); i++)
		{
			Brick* br = dynamic_cast<Brick*>(bricks[i]);
			br->SpawnCoin();
		}
		break;
	}
	y -= collisionbox.y;

}

int SwitchButton::GetObjectType()
{
	return OBJECT_TYPE_SWITCH_BUTTON;
}


