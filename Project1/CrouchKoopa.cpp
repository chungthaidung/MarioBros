#include "CrouchKoopa.h"
#include "Koopa.h"
#include "debug.h"
#include "CGame.h"
#include "Mario.h"
CrouchKoopa::CrouchKoopa(Koopa* k):WalkingKoopa(k)
{
	collisionbox.x = KOOPA_BBOX_HEIGHT;
	collisionbox.y = KOOPA_BBOX_WIDTH;
	koopa->vx = 0;
	koopa->vy = 0;
	koopa->SetGravity(MARIO_GRAVITY);
	respawntime = GetTickCount();
}

void CrouchKoopa::Update(DWORD dt)
{
	koopa->vy += koopa->GetGravity() * dt;
	koopa->CGameObject::Update(dt);
	HoldUpdate(dt);
}

void CrouchKoopa::FinalUpdate(DWORD dt)
{
	if (koopa->GetState() == KOOPA_STATE_DIE && koopa->y > CGame::GetInstance()->GetCamPos().y + SCREEN_HEIGHT)
	{
		koopa->isRemove = true;
	}
	if (koopa->GetState() == KOOPA_STATE_DIE) { 
		koopa->x += koopa->dx;
		koopa->y += koopa->dy;
		return; 
	}
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (koopa->coEResult.size() == 0)
	{
		koopa->x += koopa->dx;
		koopa->y += koopa->dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		koopa->FilterCollision(koopa->coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		koopa->x += min_tx * koopa->dx + nx * 0.4f;
		koopa->y += min_ty * koopa->dy + ny * 0.4f;

		if (nx != 0) koopa->vx *= -1;
		if (ny != 0) { 
			koopa->vy = 0; 
			koopa->vx = 0;
		}
	}
	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO )
		{
			if (koopa->GetHolder() == NULL)
			{
				koopa->nx = e->obj->Getnx();
				koopa->SetState(KOOPA_STATE_SHELL_RUNNING);
				koopa->vy = 0;
			}

		}
		else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
		{
			if (e->nx != 0) {
				koopa->SetState(KOOPA_STATE_CROUCH);
				koopa->Setny(-1);
				koopa->vy = -0.7;
				koopa->vx = e->nx*0.2;
				respawntime = GetTickCount();
			}
		}
		else if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
		{
			koopa->SetState(KOOPA_STATE_DIE);
			koopa->Setny(-1);
			koopa->vy = -0.5;
			koopa->vx = e->nx * 0.2;
		}
	}
	if (GetTickCount() - respawntime > 6000)
	{
		koopa->SetState(KOOPA_STATE_WALKING);
	}
	for (UINT i = 0; i < koopa->coEResult.size(); i++) delete koopa->coEResult[i];
	koopa->coEResult.clear();
}

void CrouchKoopa::Render()
{
	int ani = KOOPA_ANI_CROUCH;
	if (GetTickCount() - respawntime > 3500)
		ani = KOOPA_ANI_RESPAWN;
	CAnimations::GetInstance()->Get(ani)->Render(koopa->x, koopa->y, 1, koopa->nx,koopa->Getny());
	koopa->RenderBoundingBox();
}

void CrouchKoopa::HoldUpdate(DWORD dt)
{
	if (koopa->GetHolder() != NULL)
	{
		koopa->SetGravity(0);
		CMario* mario = koopa->GetHolder();
		if (mario->nx > 0)
		{
			koopa->SetPosition(mario->x + mario->GetCollisionBox().x -2, mario->y+ mario->GetCollisionBox().y-koopa->GetCollisionBox().y);
		}
		else
		{
			koopa->SetPosition(mario->x - koopa->GetCollisionBox().x +2, mario->y + mario->GetCollisionBox().y - koopa->GetCollisionBox().y);
		}
	}
	else 
	{ 
		koopa->SetGravity(MARIO_GRAVITY); 
	}

}

