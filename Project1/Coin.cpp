#include "Coin.h"
#include "CGame.h"
void Coin::Render()
{

	int ani = COIN_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}

void Coin::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void Coin::FinalUpdate(DWORD dt)
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				isRemove = true;
			}
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();
}

int Coin::GetObjectType()
{
	return OBJECT_TYPE_COIN;
}
