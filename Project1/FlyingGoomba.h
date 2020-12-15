#pragma once
#include "NormalGoomba.h"

class FlyingGoomba :
    public NormalGoomba
{
public:
    FlyingGoomba(Goomba* obj);
	virtual void Update(DWORD dt);
	virtual void Moving();
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetCollisionBox(float x, float y);
	virtual void SetState(int state);
	virtual D3DXVECTOR2 GetCollisionBox();
protected:
	int jumpcount;
	DWORD walktime;
};

