#include "Goomba.h"
#include "define.h"
#include "Mario.h"
#include "MarioTail.h"
#include "debug.h"
#include "CCollisionEvent.h"
#include "CGame.h"
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
	if (vx > 0) nx = 1;
	else nx = -1;
	vy += MARIO_GRAVITY * dt;
	CGameObject::Update(dt);
	if (vx < 0 && x < 0) {
		x = 0; vx *= -1;
	}
	//DebugOut(L"vx: %f nx: %d \n", vx,nx);
}
void Goomba::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}
void Goomba::FinalUpdate(DWORD dt)
{
	if ((state == GOOMBA_STATE_WEAPON_DIE && y>CGame::GetInstance()->GetCamPos().y+ SCREEN_HEIGHT)|| 
		(state == GOOMBA_STATE_DIE && GetTickCount() - dietime > 500))
	{
		isRemove = true;
	}
	if (state == GOOMBA_STATE_WEAPON_DIE) {
		x += dx;
		y += dy;
	}
	if (state == GOOMBA_STATE_DIE|| state == GOOMBA_STATE_WEAPON_DIE) return;
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				if (e->ny > 0) {
					SetState(GOOMBA_STATE_DIE);
					dietime = GetTickCount();
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
			{
				if (e->nx != 0)
				{
					SetState(GOOMBA_STATE_WEAPON_DIE);
					nx = e->nx;
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				SetState(GOOMBA_STATE_WEAPON_DIE);
				nx = e->nx;
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				SetState(GOOMBA_STATE_WEAPON_DIE);
				nx = e->nx;
			}
		}
	}
	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();
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
	CAnimations::GetInstance()->Get(ani)->Render(x, y, 1,nx,ny);
	RenderBoundingBox();
}
int Goomba::GetObjectType()
{
	return OBJECT_TYPE_GOOMBA;
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
	case GOOMBA_STATE_WEAPON_DIE:
		ny = -1;
		vy = -0.5;
		break;
	}
	y -= collision_box.y;
}
