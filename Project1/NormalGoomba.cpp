#include "NormalGoomba.h"
#include "Goomba.h"
#include "CGame.h"
#include "debug.h"
#include "CPlayScene.h"
#include "Mario.h"
#include "TailAttackEf.h"
#include "GoombaDieEff.h"
#include "Koopa.h"
#include "PointsEff.h"
NormalGoomba::NormalGoomba(Goomba* k)
{
	goomba = k;
	collisionbox.x = GOOMBA_BBOX_WIDTH;
	collisionbox.y = GOOMBA_BBOX_HEIGHT;
	goomba->vx = -GOOMBA_WALKING_SPEED;
}

void NormalGoomba::Update(DWORD dt)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	if (goomba->GetType() == RED_GOOMBA)
	{
		if (mario->GetPosition().x < (goomba->GetPosition().x - 48) && goomba->vx>0) goomba->vx *= -1;
		else if (mario->GetPosition().x > (goomba->GetPosition().x + 144) && goomba->vx < 0) goomba->vx *= -1;
	}
	if (goomba->vx > 0) goomba->nx = 1;
	else goomba->nx = -1;
	if (goomba->vx < 0 && goomba->x < 0) {
		goomba->x = 0; goomba->vx *= -1;
	}
	goomba->vy += GOOMBA_GRAVITY * dt;
	goomba->CGameObject::Update(dt);
	

}
void NormalGoomba::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	goomba->CalcPotentialCollisions(coObjects, goomba->coEResult);
}
void NormalGoomba::FinalUpdate(DWORD dt)
{
	Effect* eff = NULL;
	if ((goomba->state == GOOMBA_STATE_WEAPON_DIE ) || (goomba->state == GOOMBA_STATE_DIE && GetTickCount() - goomba->GetDieTime() > 500))
	{
		goomba->isRemove = true;
	}
	if (goomba->state == GOOMBA_STATE_DIE || goomba->state == GOOMBA_STATE_WEAPON_DIE) return;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (goomba->coEResult.size() == 0)
	{
		goomba->x += goomba->dx;
		goomba->y += goomba->dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		goomba->FilterCollision(goomba->coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		goomba->x += min_tx * goomba->dx + nx * 0.4f;
		goomba->y += min_ty * goomba->dy + ny * 0.4f;

		if (nx != 0) {
			goomba->vx *= -1;
		}
		if (ny != 0) {
			if (ny < 0) goomba->vy = 0;
			if (ny > 0) goomba->y -= 2;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				if (e->ny > 0 && mario->GetUntouchable() == false) {
					goomba->SetState(GOOMBA_STATE_DIE);
					goomba->SetDieTime(GetTickCount());
					CGame::GetInstance()->SetPoints(100);
					eff = new PointsEff(POINT_100_ANI);
					eff->SetPosition(goomba->x, goomba->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				}
				
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
			{
				if (e->nx != 0)
				{
					goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
					goomba->nx = e->nx;
					eff = new TailAttackEf();
					eff->SetPosition(goomba->x, goomba->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
				eff = new TailAttackEf();
				eff->SetPosition(goomba->x, goomba->y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				CGame::GetInstance()->SetPoints(100);
				eff = new PointsEff(POINT_100_ANI);
				eff->SetPosition(goomba->x, goomba->y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_CROUCH)
			{
				Koopa* koopa = dynamic_cast<Koopa*>(e->obj);
				if (koopa->GetHolder() != NULL)
				{
					goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
				}
			}
		}
	}
	
	for (UINT i = 0; i < goomba->coEResult.size(); i++) delete goomba->coEResult[i];
	goomba->coEResult.clear();
}
void NormalGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if(goomba->GetType()==GOOMBA)
	{
		ani = GOOMBA_ANI_WALKING;
		switch (goomba->state)
		{
		case GOOMBA_STATE_DIE:
			ani = GOOMBA_ANI_DIE;
			break;
		}
	}
	else if (goomba->GetType() == RED_GOOMBA)
	{
		ani = RED_GOOMBA_ANI_WALKING;

		switch (goomba->state)
		{
		case GOOMBA_STATE_DIE:
			ani = RED_GOOMBA_ANI_DIE;
			break;
		case GOOMBA_STATE_WALKING:
			ani = RED_GOOMBA_ANI_WALKING;
			break;
		}
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(goomba->x-cx, goomba->y-cy, 1, goomba->nx, goomba->ny);
	goomba->RenderBoundingBox();
}
void NormalGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = goomba->x;
	top = goomba->y;
	right = goomba->x + collisionbox.x;
	bottom = goomba->y + collisionbox.y;
}
void NormalGoomba::SetCollisionBox(float x, float y)
{
	collisionbox.x = x; 
	collisionbox.y = y; 
}
void NormalGoomba::SetState(int state)
{
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		collisionbox.y = GOOMBA_BBOX_HEIGHT_DIE;
		goomba->vx = 0;
		goomba->vy = 0;
		break;
	case GOOMBA_STATE_WEAPON_DIE:
		Effect* eff = NULL;
		if(goomba->GetType()==GOOMBA)
			eff = new GoombaDieEff(GOOMBA_ANI_WALKING);
		else eff = new GoombaDieEff(RED_GOOMBA_ANI_WALKING);
		eff->SetPosition(goomba->x, goomba->y);
		CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		break;
	}
}
D3DXVECTOR2 NormalGoomba::GetCollisionBox()
{
	return collisionbox;
}
