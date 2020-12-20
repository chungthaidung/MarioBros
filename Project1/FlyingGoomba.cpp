#include "FlyingGoomba.h"
#include "Goomba.h"
#include "debug.h"
#include "CGame.h"
#include "CPlayScene.h"
#include "Mario.h"
#include "TailAttackEf.h"
FlyingGoomba::FlyingGoomba(Goomba* obj):NormalGoomba(obj)
{
	goomba = obj;
	collisionbox.x = GOOMBA_BBOX_WIDTH;
	collisionbox.y = GOOMBA_BBOX_HEIGHT;
	jumpcount = 4;
	goomba->vy = -0.3;
}
void FlyingGoomba::Update(DWORD dt)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	if(goomba->GetType()==RED_GOOMBA)
	{
		if (mario->GetPosition().x < (goomba->GetPosition().x - 48) && goomba->vx>0) goomba->vx *= -1;
		else if (mario->GetPosition().x > (goomba->GetPosition().x + 96) && goomba->vx < 0) goomba->vx *= -1;
	}
	
	if (goomba->vx > 0) goomba->nx = 1;
	else goomba->nx = -1;
	//MovingUpdate(dt);
	goomba->vy += MARIO_GRAVITY * dt;
	if (goomba->vx < 0 && goomba->x < 0) {
		goomba->x = 0; 
		goomba->vx *= -1;
	}
	goomba->CGameObject::Update(dt);

}
void FlyingGoomba::Moving()
{
	switch (jumpcount)
	{
	case 1:
	case 2:
	case 3:
		goomba->vy = -0.3;
		break;
	case 0:
		goomba->vy = -0.65;
		break;
	case -1:
		goomba->vy == 0;
		//jumpcount = 4;
		walktime = GetTickCount();
		break;
	}
	/*if (GetTickCount() - walktime > 1000)
		jumpcount == 3;*/
}
void FlyingGoomba::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	goomba->CalcPotentialCollisions(coObjects, goomba->coEResult);
}
void FlyingGoomba::FinalUpdate(DWORD dt)
{
	if ((goomba->state == GOOMBA_STATE_WEAPON_DIE && goomba->y > CGame::GetInstance()->GetCamPos().y + SCREEN_HEIGHT))
	{
		goomba->isRemove = true;
	}
	if (goomba->state == GOOMBA_STATE_WEAPON_DIE) {
		goomba->x += goomba->dx;
		goomba->y += goomba->dy;
	}
	if (goomba->state == GOOMBA_STATE_WEAPON_DIE) return;
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

		if (nx != 0)goomba->vx *= -1;
		if (ny != 0) {
			goomba->vy = 0;
			if (ny < 0)
			{
				Moving();
				jumpcount--;
				//DebugOut(L"JUMP COUNT: %d \n", jumpcount);

				//goomba->vy = -0.3;
			}
			if (ny > 0) goomba->y -= 2;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{

				if (e->ny > 0) {
					goomba->SetState(GOOMBA_STATE_WALKING);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
			{
				if (e->nx != 0)
				{
					
					goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
					goomba->nx = e->nx;
					TailAttackEf* eff = new TailAttackEf();
					eff->SetPosition(goomba->x, goomba->y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
				goomba->nx = e->nx;
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING)
			{
				goomba->SetState(GOOMBA_STATE_WEAPON_DIE);
				goomba->nx = e->nx;
			}
		}
	}
	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < goomba->coEResult.size(); i++) delete goomba->coEResult[i];
	goomba->coEResult.clear();
	if (GetTickCount() - walktime > 800 && jumpcount < -1)
	{
		jumpcount = 4;
	}
}
void FlyingGoomba::Render()
{
	int ani = GOOMBA_FLY_ANI_FLY;

	if (goomba->GetType() == RED_GOOMBA)
	{
		ani = RED_GOOMBA_FLY_ANI_FLY;
		if(jumpcount<-1)
			ani = RED_GOOMBA_FLY_ANI_WALK;
		if(goomba->GetState()== GOOMBA_STATE_WEAPON_DIE)
			ani = RED_GOOMBA_ANI_WALKING;
	}
	else if (goomba->GetType() == GOOMBA)
	{
		if (jumpcount < -1)
			ani = GOOMBA_FLY_ANI_WALK;
		if (goomba->GetState() == GOOMBA_STATE_WEAPON_DIE)
			ani = GOOMBA_ANI_WALKING;

	}
	CAnimations::GetInstance()->Get(ani)->Render(goomba->x, goomba->y, 1, goomba->nx, goomba->ny);
	goomba->RenderBoundingBox();
}
void FlyingGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = goomba->x;
	top = goomba->y;
	right = goomba->x + collisionbox.x;
	bottom = goomba->y + collisionbox.y;
}
void FlyingGoomba::SetCollisionBox(float x, float y)
{
	collisionbox.x = x;
	collisionbox.y = y;
}
void FlyingGoomba::SetState(int state)
{
	switch (state)
	{
	case GOOMBA_STATE_WEAPON_DIE:
		goomba->ny = -1;
		goomba->vy = -0.5;
		break;
	}
	
}
D3DXVECTOR2 FlyingGoomba::GetCollisionBox()
{
	return collisionbox;
}