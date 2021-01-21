#include "FlyingKoopa.h"
#include "Koopa.h"
#include "debug.h"
#include "TailAttackEf.h"
#include "CGame.h"
#include "PointsEff.h"
FlyingKoopa::FlyingKoopa(Koopa* k):WalkingKoopa(k)
{
	koopa = k;
	collisionbox.x = KOOPA_BBOX_HEIGHT;
	collisionbox.y = KOOPA_BBOX_WIDTH;
	koopa->SetGravity(MARIO_GRAVITY);
	koopa->vx = -KOOPA_WALKING_SPEED;
}

FlyingKoopa::~FlyingKoopa()
{
}

void FlyingKoopa::Update(DWORD dt)
{
	if (koopa->vx > 0)koopa->nx = 1;
	else koopa->nx = -1;
	koopa->vy += koopa->GetGravity() * dt;
	koopa->CGameObject::Update(dt);
}

void FlyingKoopa::FinalUpdate(DWORD dt)
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
			if (ny < 0) koopa->vy = -KOOPA_JUMP_FORCE;
			if (ny > 0) koopa->y -= 2;

		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				if (e->ny > 0 && mario->GetUntouchable() == false){
					koopa->SetState(KOOPA_STATE_WALKING);
					CGame::GetInstance()->SetPoints(100);
					PointsEff* eff = new PointsEff(POINT_100_ANI);
					eff->SetPosition(koopa->x, koopa->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
					//koopa->SetGravity(0);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL )
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
			else if ((e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING) || e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				CGame::GetInstance()->SetPoints(100);
				PointsEff* eff = new PointsEff(POINT_100_ANI);
				eff->SetPosition(koopa->x, koopa->y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				koopa->SetState(KOOPA_STATE_DIE);
				
			}
		}
	}
	for (UINT i = 0; i < koopa->coEResult.size(); i++) delete koopa->coEResult[i];
	koopa->coEResult.clear();
}

void FlyingKoopa::Render()
{
	int ani = KOOPA_ANI_FLY;
	int f = -1;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(koopa->x-cx, koopa->y-cy, 1, koopa->nx*f, koopa->Getny());
	koopa->RenderBoundingBox();
}

