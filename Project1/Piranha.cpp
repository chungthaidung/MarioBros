#include "Piranha.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
#include "Mario.h"
#include "CPlayScene.h"
#include "EnemyDamagedEff.h"
Piranha::Piranha(int t, int ny, float start_y)
{
	type = t;
	this->ny = ny;
	//DebugOut(L"NY: %d\n", ny);
	y_start = start_y;
	SetState(PIRANHA_STATE_UP);
	isEnemy = true;
	renderOrder = 1;
}

void Piranha::Update(DWORD dt)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	if (y > y_start && state == PIRANHA_STATE_DOWN)
	{
		y = y_start;
		if (mario->GetPosition().x > x - 72 && mario->GetPosition().x < x + PIRANHA_BBOX_WIDTH + 72)
			SetState(PIRANHA_STATE_DOWN);
		else
			SetState(PIRANHA_STATE_UP);
	}
	else if (y < y_start - 102 && state == PIRANHA_STATE_UP)
	{
		y = y_start - 102;
		SetState(PIRANHA_STATE_STAY);
	}
	else if (state == PIRANHA_STATE_STAY && GetTickCount() - staytime > 1000)
	{
		SetState(PIRANHA_STATE_DOWN);
	}
	CGameObject::Update(dt);
}

void Piranha::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void Piranha::FinalUpdate(DWORD dt)
{
	y += dy;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	/*if (coEResult.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{*/
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if ((e->obj->GetObjectType() == OBJECT_TYPE_TAIL || e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL) && e->nx != 0)
		{
			EnemyDamagedEff* eff = new EnemyDamagedEff();
			eff->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
			isRemove = true;
		}
	}
	//}
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
}

void Piranha::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_STATE_UP:
		vy = -0.05f;
		break;
	case PIRANHA_STATE_DOWN:
		vy = 0.05f;
		break;
	case PIRANHA_STATE_STAY:
		vy = 0.0f;
		staytime = GetTickCount();
		break;
	}
}

void Piranha::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + PIRANHA_BBOX_WIDTH;
	bottom = y + PIRANHA_BBOX_HEIGHT;
}

void Piranha::Render()
{
	int ani = GREEN_PIRANHA_ANI;
	if(type==RED_TYPE)
		ani = RED_PIRANHA_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy,1,1,ny);
	RenderBoundingBox();
}

int Piranha::GetObjectType()
{
	return OBJECT_TYPE_PIRANHA;
}

int Piranha::GetType()
{
	return type;
}
