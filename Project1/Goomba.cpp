#include "Goomba.h"
#include "define.h"
#include "Mario.h"
#include "MarioTail.h"
#include "debug.h"
#include "CCollisionEvent.h"
Goomba::Goomba()
{
	SetState(GOOMBA_STATE_WALKING);
	collision_box.x = GOOMBA_BBOX_WIDTH;
	collision_box.y = GOOMBA_BBOX_HEIGHT;
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + collision_box.x;
	bottom = y + collision_box.y;
	
}

void Goomba::Update(DWORD dt)
{
	CGameObject::Update(dt);
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

}

void Goomba::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	coEResult.clear();
	CalcPotentialCollisions(coObjects, coEResult);
}

void Goomba::FinalUpdate(DWORD dt)
{
	if (state == GOOMBA_STATE_DIE) return;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (coEResult.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx *= -1;
		if (ny != 0) vy = 0;
	}
	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
		{
			if (e->ny > 0) {
				SetState(GOOMBA_STATE_DIE);
				//	DebugOut(L"aaaa \n");
			}
		}
		if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
		{
			if (e->nx != 0)
			{
				SetState(GOOMBA_STATE_DIE);
				dietime = GetTickCount();

			}
		}
		if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
		{
			SetState(GOOMBA_STATE_DIE);
			dietime = GetTickCount();

			DebugOut(L"Goomba...\n");
		}
	}

	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
}

void Goomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		ani = GOOMBA_ANI_DIE;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y, 1,nx);
	RenderBoundingBox();
}
int Goomba::GetObjectType()
{
	return 2;
}
void Goomba::SetState(int state)
{
	CGameObject::SetState(state);
	y += collision_box.y;
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		collision_box.y = GOOMBA_BBOX_HEIGHT_DIE;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
	y -= collision_box.y;
}
