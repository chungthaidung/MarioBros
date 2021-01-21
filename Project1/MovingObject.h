#pragma once
#include "CGameObject.h"
#define MOVING_OBJECT_BBOX_WIDTH 144
#define MOVING_OBJECT_BBOX_HEIGHT 48
#define MOVING_OBJECT_ANI	615
#define MOVING_OBJECT_STATE_FALL	1
#define MOVING_OBJECT_STATE_MOVING	0
class MovingObject :
    public CGameObject
{
public:
	MovingObject();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
protected:
	float gravity;
	DWORD timing;
};

