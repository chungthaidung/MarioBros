#include "EndGameReward.h"

EndGameReward::EndGameReward():CGameObject()
{
	state = END_GAME_REWARD_STATE_FLOWER;
}

void EndGameReward::Update(DWORD dt)
{

	CGameObject::Update(dt);
}

void EndGameReward::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void EndGameReward::FinalUpdate(DWORD dt)
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}
}

void EndGameReward::SetState(int state)
{
}

void EndGameReward::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + END_GAME_REWARD_BBBOX_WIDTH;
	bottom = y + END_GAME_REWARD_BBBOX_HEIGHT;
}

void EndGameReward::Render()
{
}

int EndGameReward::GetObjectType()
{
	return OBJECT_TYPE_END_GAME_REWARD;
}
