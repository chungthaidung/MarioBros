#pragma once
#include "CGameObject.h"
#define UP_MUSHROOM_BBOX_WIDTH 48
#define UP_MUSHROOM_BBOX_HEIGHT 48

#define UP_MUSHROOM_VELOCITY 0.15f

#define UP_MUSHROOM_STATE_UP 1
#define UP_MUSHROOM_STATE_MOVE 2

#define UP_MUSHROOM_ANI	616

class UpMushroom :
    public CGameObject
{
public:
	UpMushroom(float y_s);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	void SetGravity(float g);
protected:
	float gravity;
	float y_start;
};

