#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "CGameObject.h"
class Goomba;
class NormalGoomba
{
public:
	NormalGoomba(Goomba* k);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetCollisionBox(float x, float y);
	virtual void SetState(int state);
	virtual D3DXVECTOR2 GetCollisionBox();

protected:
	Goomba* goomba;
	D3DXVECTOR2 collisionbox;
};

