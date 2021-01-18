#pragma once
#include "CGameObject.h"
#include "define.h"

#define COIN_BBOX_WIDTH  48
#define COIN_BBOX_HEIGHT 48
class Coin :
    public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
};

