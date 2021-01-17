#include "EndGameReward.h"
#include "debug.h"
#include "EndGameRewardEff.h"
#include "CGame.h"
EndGameReward::EndGameReward():CGameObject()
{
	state = END_GAME_REWARD_STATE_MUSHROOM;
}
void EndGameReward::Update(DWORD dt)
{
	if (GetTickCount() - changetime > 100)
	{
		if (state == END_GAME_REWARD_STATE_MUSHROOM)
			SetState(END_GAME_REWARD_STATE_FLOWER);
		else if (state == END_GAME_REWARD_STATE_FLOWER)
			SetState(END_GAME_REWARD_STATE_STAR);
		else if (state == END_GAME_REWARD_STATE_STAR)
			SetState(END_GAME_REWARD_STATE_MUSHROOM);
	}
	//DebugOut(L"[INFO] REWARD: %d\n", reward);
	CGameObject::Update(dt);
}
void EndGameReward::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}
void EndGameReward::FinalUpdate(DWORD dt)
{
	if (state == END_GAME_REWARD_STATE_EMPTY) return;
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
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				CMario* mr = dynamic_cast<CMario*>(e->obj);
				mr->SetLockControl(true);
				SetState(END_GAME_REWARD_STATE_EMPTY);
				mr->endgame_reward.push_back(reward);
			//	DebugOut(L"STATE REWARD: %d \n", reward);
			}
		}
	}
}
void EndGameReward::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case END_GAME_REWARD_STATE_FLOWER:
		changetime = GetTickCount();
		reward = FLOWER;
		break;
	case END_GAME_REWARD_STATE_MUSHROOM:
		changetime = GetTickCount();
		reward = MUSHROOM;
		break;
	case END_GAME_REWARD_STATE_STAR:
		changetime = GetTickCount();
		reward = STAR;
		break;
	case END_GAME_REWARD_STATE_EMPTY:
		int ani = END_GAME_REWARD_EFFECT_ANI_MUSHROOM;
		if (reward == FLOWER)
			ani = END_GAME_REWARD_EFFECT_ANI_FLOWER;
		else if (reward == STAR)
			ani = END_GAME_REWARD_EFFECT_ANI_STAR;
		EndGameRewardEff* eff = new EndGameRewardEff(ani);
		eff->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		break;
	}
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
	int ani = END_GAME_REWARD_ANI_FLOWER;
	switch (state)
	{
	case END_GAME_REWARD_STATE_FLOWER:
		ani = END_GAME_REWARD_ANI_FLOWER;
		break;
	case END_GAME_REWARD_STATE_MUSHROOM:
		ani = END_GAME_REWARD_ANI_MUSHROOM;
		break;
	case END_GAME_REWARD_STATE_STAR:
		ani = END_GAME_REWARD_ANI_STAR;
		break;
	case END_GAME_REWARD_STATE_EMPTY:
		ani = END_GAME_REWARD_ANI_EMPTY;
		break;
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}
int EndGameReward::GetObjectType()
{
	return OBJECT_TYPE_END_GAME_REWARD;
}
