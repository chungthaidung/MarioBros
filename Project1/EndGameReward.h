#pragma once
#include "CGameObject.h"
#include "Mario.h"
#define END_GAME_REWARD_BBBOX_WIDTH	48
#define END_GAME_REWARD_BBBOX_HEIGHT	48

#define END_GAME_REWARD_STATE_MUSHROOM	1
#define END_GAME_REWARD_STATE_FLOWER	2
#define END_GAME_REWARD_STATE_STAR	3
#define END_GAME_REWARD_STATE_EMPTY	0

#define MUSHROOM	1
#define FLOWER	2
#define STAR	3

#define END_GAME_REWARD_ANI_FLOWER	607
#define END_GAME_REWARD_ANI_MUSHROOM	608
#define END_GAME_REWARD_ANI_STAR	609
#define END_GAME_REWARD_ANI_EMPTY	610

#define END_GAME_REWARD_EFFECT_ANI_FLOWER	504
#define END_GAME_REWARD_EFFECT_ANI_MUSHROOM	505
#define END_GAME_REWARD_EFFECT_ANI_STAR	506

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
protected:
	DWORD changetime;
	int reward;
};