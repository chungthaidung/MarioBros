#include "WorldMario.h"

WorldMario::WorldMario()
{
	vx = 0; 
	vy = 0;
}

void WorldMario::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void WorldMario::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void WorldMario::FinalUpdate(DWORD dt)
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
		if (nx != 0)  vx =0;
		if (ny != 0)
		{
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
}

void WorldMario::Render()
{
	int ani = MARIO_WORLD_ANI_SMALL;
	switch (level_p)
	{
	case MARIO_LEVEL_SMALL:
		ani = MARIO_WORLD_ANI_SMALL;
		break;
	case MARIO_LEVEL_BIG:
		ani = MARIO_WORLD_ANI_BIG;
		break;
	case MARIO_LEVEL_RACOON:
		ani = MARIO_WORLD_ANI_RACOON;
		break;
	case MARIO_LEVEL_FIRE:
		ani = MARIO_WORLD_ANI_FIRE;
		break;
	}
}

void WorldMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_WORLD_BBOX_WIDTH;
	bottom = y + MARIO_WORLD_BBOX_HEIGHT;
}

int WorldMario::GetObjectType()
{
	return OBJECT_TYPE_WORLD_MARIO;
}

void WorldMario::SetLevel(int level)
{
	level_p = level;
}
