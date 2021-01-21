#include "MovingObject.h"
#include "CGame.h"
bool MovingObject::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
		return false;
    return true;
}

MovingObject::MovingObject():CGameObject()
{
	state= MOVING_OBJECT_STATE_MOVING;
    vx = -0.1;
    gravity = 0;
}

void MovingObject::Update(DWORD dt)
{
    vy += gravity * dt;
    CGameObject::Update(dt);
}

void MovingObject::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CalcPotentialCollisions(coObjects, coEResult);
}

void MovingObject::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	x += dx;
	y += dy;
	if (coEResult.size() == 0)
	{
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO && e->ny>0 && state!= MOVING_OBJECT_STATE_FALL)
			{
				SetState(MOVING_OBJECT_STATE_FALL);
			}
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
	if (state== MOVING_OBJECT_STATE_FALL && GetTickCount() - timing > 200)
	{
		gravity = 0.001;
	}
	if (y > CGame::GetInstance()->GetCurrentScene()->GetBoundary().bottom)
		isRemove = true;

}

void MovingObject::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MOVING_OBJECT_STATE_MOVING:
		vx = -0.2;
		gravity = 0;
		break;
	case MOVING_OBJECT_STATE_FALL:
		vx = 0;
		timing = GetTickCount();
		break;
	}
}

void MovingObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MOVING_OBJECT_BBOX_WIDTH;
	bottom = y + MOVING_OBJECT_BBOX_HEIGHT;
}

void MovingObject::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(MOVING_OBJECT_ANI)->Render(x-cx, y-cy);
}

int MovingObject::GetObjectType()
{
	return OBJECT_TYPE_MOVING_OBJECT;
}
