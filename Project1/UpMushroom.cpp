#include "UpMushroom.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
UpMushroom::UpMushroom(float y_s) :CGameObject()
{
	y = y_s;
	y_start = y_s;

}

void UpMushroom::Update(DWORD dt)
{
	if (y < y_start - 50 && state == UP_MUSHROOM_STATE_UP)
	{
		SetState(UP_MUSHROOM_STATE_MOVE);
	}
	vy += gravity * dt;
	CGameObject::Update(dt);
}

void UpMushroom::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void UpMushroom::FinalUpdate(DWORD dt)
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

void UpMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case UP_MUSHROOM_STATE_UP:
		vy = -0.1;
		vx = 0;
		gravity = 0;
		break;
	case UP_MUSHROOM_STATE_MOVE:
		gravity = MARIO_GRAVITY;
		vy = 0;
		vx = UP_MUSHROOM_VELOCITY * nx;
		break;

	}

}

void UpMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + UP_MUSHROOM_BBOX_WIDTH;
	bottom = y + UP_MUSHROOM_BBOX_HEIGHT;
}

void UpMushroom::Render()
{
	int ani = UP_MUSHROOM_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x - cx, y - cy);
	RenderBoundingBox();

}

int UpMushroom::GetObjectType()
{
	return OBJECT_TYPE_UP_MUSHROOM;
}

bool UpMushroom::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_GHOST && (direction.y > 0 || direction.x != 0))
		return true;
	if (obj->isEnemy)
		return true;
	if (obj->GetObjectType() == OBJECT_TYPE_COIN)
		return true;
	if (obj->GetState() == BRICK_COIN && obj->GetObjectType() == OBJECT_TYPE_BRICK) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_END_GAME_REWARD) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
	{
		CMario* mario = dynamic_cast<CMario*>(obj);
		if (mario->GetUntouchable() == true) return true;
	}
	return false;
}

void UpMushroom::SetGravity(float g)
{
	gravity = g;
}
