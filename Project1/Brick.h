#pragma once
#include "QuestionBox.h"
#include "Coin.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

#define BRICK_ANI_REWARD		605
#define BRICK_ANI_EMPTY		604
#define BRICK_ANI_BROKEN		606

#define BRICK_REWARD 1
#define BRICK_BOUNC 12
#define BRICK_EMPTY 13

#define BRICK_BREAKABLE 2
#define BRICK_BROKEN 21
#define BRICK_COIN 22
class Brick :
    public QuestionBox
{
public:
    Brick(int obj_type,int type, float y = 0.0f);
	~Brick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual int GetObjectType();
	virtual void SetWidthHeight(int w, int h);
	virtual void SpawnCoin();
	virtual void DespawnCoin();
protected:
	Coin* coin;
};

