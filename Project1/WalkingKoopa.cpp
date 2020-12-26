#include "WalkingKoopa.h"
#include "Koopa.h"
#include "debug.h"
#include "TailAttackEf.h"
#include "CGame.h"
#include "PointsEff.h"
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
	if (koopa->vx < 0 && koopa->x < 0) {
		koopa->x = 0; koopa->vx *= -1;
	}
	if (koopa->vx > 0)koopa->nx = 1;
	else koopa->nx = -1;
	koopa->vy += koopa->GetGravity() * dt;
	koopa->CGameObject::Update(dt);
	
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
		if (ny != 0)
		{
			koopa->vy = 0;
			if (ny > 0) koopa->y -= 2;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				if (e->ny > 0) {
					koopa->SetState(KOOPA_STATE_CROUCH);
					PointsEff* eff = new PointsEff(POINT_100_ANI);
					eff->SetPosition(koopa->x, koopa->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
					koopa->vy = 0;
					koopa->Setny(1);
					//koopa->SetGravity(0);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
			{
				if (e->nx != 0) {
					koopa->SetState(KOOPA_STATE_CROUCH);
					koopa->Setny(-1);
					koopa->vy = -0.5;
					TailAttackEf* eff = new TailAttackEf();
					eff->SetPosition(koopa->x, koopa->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL || (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING))
			{
				PointsEff* eff = new PointsEff(POINT_100_ANI);
				eff->SetPosition(koopa->x, koopa->y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				koopa->SetState(KOOPA_STATE_DIE);
			}
			else if ((e->obj->GetObjectType() == OBJECT_TYPE_GHOST || e->obj->GetObjectType() == OBJECT_TYPE_GROUND || e->obj->GetObjectType() == OBJECT_TYPE_BRICK )&&koopa->GetType()==RED_KOOPA)
			{
				if (e->ny < 0)
				{
					float l, t, r, b;
					koopa->GetBoundingBox(l, t, r, b);
					//DebugOut(L" e->obj width: %f \n", e->obj->GetWidthHeight().x);

					if (l < (e->obj->x - (koopa->GetCollisionBox().x / 2))&& koopa->nx == -1)
					{
						koopa->x = e->obj->x - koopa->GetCollisionBox().x / 2;
						//DebugOut(L"[INFO] left: %f || e->obj l: %f || koopa nx: %d  || e->obj r: %f \n", l, e->obj->x, koopa->nx,  e->obj->width);
						koopa->vx *= -1;
					}
					else if (l > (e->obj->x + e->obj->width - (koopa->GetCollisionBox().x / 2)) && koopa->nx == 1)
					{
						koopa->x = e->obj->x + e->obj->width - koopa->GetCollisionBox().x / 2;
						koopa->vx *= -1;
						//DebugOut(L"[INFO] left: %f || e->obj l: %f || koopa nx: %d  || e->obj r: %f \n", l, e->obj->x, koopa->nx,  e->obj->width);
					}
					//DebugOut(L"[INFO] left: %f || e->obj l: %f || right: %f  || e->obj r: %f \n", l, e->obj->x, r, (e->obj->x + e->obj->width));
				}
			}
		}
	}	
	for (UINT i = 0; i < koopa->coEResult.size(); i++) delete koopa->coEResult[i];
	koopa->coEResult.clear();
}
void WalkingKoopa::Render()
{
	int ani = KOOPA_ANI_WALKING;
	if (koopa->GetType() == RED_KOOPA) ani = RED_KOOPA_ANI_WALKING;
	int f = -1;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(koopa->x-cx, koopa->y-cy, 1, koopa->nx*f);
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
