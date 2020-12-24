#include "SuperMushroom.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
SuperMushroom::SuperMushroom( float y_s) :CGameObject()
{
	y = y_s;
	y_start = y_s;

}

void SuperMushroom::Update(DWORD dt)
{
	if (y < y_start - 50 && state==SUPER_MUSHROOM_STATE_UP)
	{
		SetState(SUPER_MUSHROOM_STATE_MOVE);
	}
	vy += gravity * dt;
	CGameObject::Update(dt);
}

void SuperMushroom::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void SuperMushroom::FinalUpdate(DWORD dt)
{
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

		if (nx != 0) {
			vx *= -1;
		}
		if (ny != 0) {
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			//DebugOut(L"COEVENT RESULT SIZE: %d \n", coEventsResult.size());

			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				CGame::GetInstance()->GetCurrentScene()->DespawnObject(this);

			}
		}
	}
	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
}

void SuperMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPER_MUSHROOM_STATE_UP:
		vy = -0.1;
		vx = 0;
		gravity = 0;
		break;
	case SUPER_MUSHROOM_STATE_MOVE:
		gravity = MARIO_GRAVITY;
		vy = 0;
		vx = SUPER_MUSHROOM_VELOCITY*nx;
		break;

	}
	
}

void SuperMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SUPER_MUSHROOM_BBOX_WIDTH;
	bottom = y + SUPER_MUSHROOM_BBOX_HEIGHT;
}

void SuperMushroom::Render()
{
	int ani = SUPER_MUSHROOM_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();

}

int SuperMushroom::GetObjectType()
{
	return OBJECT_TYPE_SUPER_MUSHROOM;
}

void SuperMushroom::SetGravity(float g)
{
	gravity = g;
}
