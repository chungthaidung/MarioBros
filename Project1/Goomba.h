#pragma once
#include "CGameObject.h"
class Goomba :
    public CGameObject
{
public:
	Goomba();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();

	virtual int GetObjectType();
protected:
	DWORD dietime;
	D3DXVECTOR2 collision_box;
};

