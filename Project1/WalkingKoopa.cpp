#include "WalkingKoopa.h"
#include "Koopa.h"
#include "debug.h"
WalkingKoopa::WalkingKoopa(Koopa* k)
{
	koopa = k;
	collisionbox.x = KOOPA_BBOX_HEIGHT;
	collisionbox.y = KOOPA_BBOX_WIDTH;
	koopa->vx = -KOOPA_WALKING_SPEED;
	koopa->SetGravity(MARIO_GRAVITY);
}
void WalkingKoopa::Update(DWORD dt)
{
	if (koopa->vx > 0)koopa->nx = 1;
	else koopa->nx = -1;
	koopa->vy += koopa->GetGravity() * dt;
	koopa->CGameObject::Update(dt);
	if (koopa->vx < 0 && koopa->x < 0) {
		koopa->x = 0; koopa->vx *=-1;
	}
}
void WalkingKoopa::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	koopa->CalcPotentialCollisions(colliable_objects, koopa->coEResult);
}
void WalkingKoopa::FinalUpdate(DWORD dt)
{
//	if (koopa->state != KOOPA_STATE_WALKING) return;
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
		if (ny != 0) koopa->vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				if (e->ny > 0) {
					koopa->SetState(KOOPA_STATE_CROUCH);
					koopa->vy = 0;
					koopa->Setny(1);
					//koopa->SetGravity(0);
				}
			}
			else if ( e->obj->GetObjectType() == OBJECT_TYPE_TAIL|| e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				if (e->nx != 0) {
					koopa->SetState(KOOPA_STATE_CROUCH);
					koopa->Setny(-1);
					koopa->vy = -0.5;
				}
			}
		}
		
	}
	//
	// Collision logic with other objects
	//
	
	for (UINT i = 0; i < koopa->coEResult.size(); i++) delete koopa->coEResult[i];
	koopa->coEResult.clear();
}

void WalkingKoopa::Render()
{
	int ani = KOOPA_ANI_WALKING;
	int f = -1;
	CAnimations::GetInstance()->Get(ani)->Render(koopa->x, koopa->y, 1, koopa->nx*f);
	koopa->RenderBoundingBox();
}

void WalkingKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	koopa->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}

D3DXVECTOR2 WalkingKoopa::GetCollisionBox()
{
	return collisionbox;
}
