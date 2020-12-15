#pragma once
#include "CGameObject.h"

#define END_GAME_REWARD_BBBOX_WIDTH	48
#define END_GAME_REWARD_BBBOX_HEIGHT	48

#define END_GAME_REWARD_STATE_FLOWER	1
#define END_GAME_REWARD_STATE_MUSHROOM	2
#define END_GAME_REWARD_STATE_STAR	3
#define END_GAME_REWARD_STATE_EMPTY	0
class EndGameReward :
    public CGameObject
{
public:
	EndGameReward();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
};

