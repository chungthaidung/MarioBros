#include "RunningShell.h"
#include "Koopa.h"
#include "debug.h"
#include "Brick.h"
RunningShell::RunningShell(Koopa* k):WalkingKoopa(k)
{
	collisionbox.x = KOOPA_BBOX_HEIGHT;
	collisionbox.y = KOOPA_BBOX_WIDTH;
	koopa->vx = koopa->Getnx()*SHELL_SPEED;
	koopa->SetGravity(MARIO_GRAVITY);
}

void RunningShell::Update(DWORD dt)
{
	koopa->vy += koopa->GetGravity() * dt;
	koopa->CGameObject::Update(dt);
}
void RunningShell::FinalUpdate(DWORD dt)
{
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
			if (ny > 0) koopa->y -= 2;
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL || e->obj->GetObjectType() == OBJECT_TYPE_TAIL )
			{
				if (e->nx != 0) {
					koopa->SetState(KOOPA_STATE_CROUCH);
					koopa->Setny(-1);
					koopa->vy = -0.5;
					koopa->vx = e->nx * 0.2;
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_GOOMBA || e->obj->GetObjectType() == OBJECT_TYPE_KOOPA ||( e->obj->GetObjectType() == OBJECT_TYPE_BRICK && e->obj->GetState() == BRICK_BREAKABLE))
			{
				if (e->nx != 0) 
				{
					koopa->vx *= -1;
					koopa->x += koopa->dx;
				}
			}
		}
	}
	for (UINT i = 0; i < koopa->coEResult.size(); i++) delete koopa->coEResult[i];
	koopa->coEResult.clear();
}

void RunningShell::Render()
{
	int ani = KOOPA_SHELL_ANI_RUN;
	if (koopa->GetType() == RED_KOOPA) ani = RED_KOOPA_SHELL_ANI_RUN;
	CAnimations::GetInstance()->Get(ani)->Render(koopa->x, koopa->y, 1, koopa->nx,koopa->Getny());
	koopa->RenderBoundingBox();
}


