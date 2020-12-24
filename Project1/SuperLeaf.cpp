#include "SuperLeaf.h"
#include "debug.h"
#include "CGame.h"
#include "define.h"
SuperLeaf::SuperLeaf(float x_s, float y_s)
{
	x_start = x_s;
	y_start = y_s;
}

void SuperLeaf::Update(DWORD dt)
{
	if (state == SUPER_LEAF_STATE_UP && y < y_start - 96)
	{
		y = y_start - 96;
		vy = 0;
		SetState(SUPER_LEAF_STATE_RIGHT);
	}
	vy += gravity * dt;
	if (vy > SUPER_LEAF_GRAVITY * dt)
		vy = gravity * dt;
	CGameObject::Update(dt);
	//DebugOut(L"[INFO] SUPER LEAF x: %f || y: %f \n", x, y);
}

void SuperLeaf::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void SuperLeaf::FinalUpdate(DWORD dt)
{
	if (y > CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y + SCREEN_HEIGHT)
	{
		CGame::GetInstance()->GetCurrentScene()->DespawnObject(this);
	}
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	
	x += dx;
	y += dy;
	//if (state == SUPER_LEAF_STATE_UP) return;
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
		{
			isRemove = true;
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();
	
	 if (state == SUPER_LEAF_STATE_RIGHT && x > x_start + 96)
	{
		x = x_start + 96;
		vy = 0;
		SetState(SUPER_LEAF_STATE_LEFT);
	}
	else if (state == SUPER_LEAF_STATE_LEFT && x < x_start)
	{
		x = x_start ;
		vy = 0;
		SetState(SUPER_LEAF_STATE_RIGHT);
	}
}

void SuperLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPER_LEAF_STATE_UP:
		vy = -0.3;
		vx = 0;
		break;
	case SUPER_LEAF_STATE_RIGHT:
		nx = 1;
		vx = SUPER_LEAF_VELOCITY_X *nx;
		gravity = MARIO_GRAVITY;
		break;
	case SUPER_LEAF_STATE_LEFT:
		nx = -1;
		vx = SUPER_LEAF_VELOCITY_X *nx;
		gravity = MARIO_GRAVITY;
		break;
	}
}

void SuperLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SUPER_LEAF_BBOX_WIDTH;
	bottom = y + SUPER_LEAF_BBOX_HEIGHT;
}

void SuperLeaf::Render()
{
	int f = -1;
	int ani = SUPER_LEAF_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy,1,nx*f);
	RenderBoundingBox();
}

int SuperLeaf::GetObjectType()
{
	return OBJECT_TYPE_SUPER_LEAF;
}

void SuperLeaf::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	x_start = x;
}

void SuperLeaf::SetGravity(float g)
{
	gravity = g;
}

void SuperLeaf::SetXStart(float x_s)
{
	x_start = x_s;
}
