#pragma once
#include "CGameObject.h"
#define FLOATING_KOOPA_STATE_UP 0
#define FLOATING_KOOPA_STATE_DOWN 1
#define FLOATING_KOOPA_STATE_FALL	2

class FloatingKoopa :
    public CGameObject
{
public:
	FloatingKoopa(float a, float b);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);

	virtual void Render();
	virtual int GetObjectType();

	void SetGravity(float a);
	float GetGravity();
protected:
	float gravity;
	float top_limit, bottom_limit;
};

