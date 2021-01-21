#include "FloatingKoopa.h"
#include "define.h"
#include "CGame.h"
#include "TailAttackEf.h"
#include "PointsEff.h"
FloatingKoopa::FloatingKoopa(float a, float b)
{
	top_limit = a;
	bottom_limit = b;
	isEnemy = true;
	SetState(FLOATING_KOOPA_STATE_DOWN);
	vx = 0;
}

void FloatingKoopa::Update(DWORD dt)
{
	if (y < top_limit && state == FLOATING_KOOPA_STATE_UP)
	{
		SetState(FLOATING_KOOPA_STATE_DOWN);
	}
	else if (y+KOOPA_BBOX_HEIGHT > bottom_limit && state == FLOATING_KOOPA_STATE_DOWN)
	{
		SetState(FLOATING_KOOPA_STATE_UP);
	}
	vy += gravity * dt;
	CGameObject::Update(dt);
}

void FloatingKoopa::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void FloatingKoopa::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if ( coEResult.size() == 0)
	{
		 x +=  dx;
		 y +=  dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		 FilterCollision( coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		 x += min_tx *  dx + nx * 0.4f;
		 y += min_ty *  dy + ny * 0.4f;


		/*if (nx != 0)  vx *= -1;
		if (ny != 0) {
		}*/

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				if (e->ny > 0)
				{
					PointsEff* eff = new PointsEff(POINT_200_ANI);
					CGame::GetInstance()->SetPoints(200);
					eff->SetPosition(x,y);
					CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
					SetState(FLOATING_KOOPA_STATE_FALL);
				}
			}
			else if (e->obj->GetObjectType() == OBJECT_TYPE_TAIL)
			{
				TailAttackEf* eff = new TailAttackEf();
				eff->SetPosition(x,y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				SetState(FLOATING_KOOPA_STATE_FALL);
			}
			else if ((e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING) || e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL)
			{
				CGame::GetInstance()->SetPoints(100);
				PointsEff* eff = new PointsEff(POINT_100_ANI);
				eff->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
				SetState(FLOATING_KOOPA_STATE_FALL);
			}
		}
	}
	for (UINT i = 0; i <  coEResult.size(); i++) delete  coEResult[i];
	 coEResult.clear();	 
}

void FloatingKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOATING_KOOPA_STATE_DOWN:
		vy = 0.1;
		gravity = 0;
		break;
	case FLOATING_KOOPA_STATE_UP:
		vy = -0.1;
		gravity = 0;
		break;
	case FLOATING_KOOPA_STATE_FALL:
		vy = 0;
		gravity = MARIO_GRAVITY;
		break;

	}
}

void FloatingKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPA_BBOX_WIDTH;
	bottom = y + KOOPA_BBOX_HEIGHT;
}

bool FloatingKoopa::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	return false;
}

void FloatingKoopa::Render()
{
	int ani = RED_KOOPA_ANI_FLY;
	
	if (state == FLOATING_KOOPA_STATE_FALL)
		ani = RED_KOOPA_ANI_WALKING;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x - cx, y - cy);
	RenderBoundingBox();
}

int FloatingKoopa::GetObjectType()
{
	return OBJECT_TYPE_FLOATING_KOOPA;
}

void FloatingKoopa::SetGravity(float a)
{
	gravity = a;
}

float FloatingKoopa::GetGravity()
{
	return gravity;
}
