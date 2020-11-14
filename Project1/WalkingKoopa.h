#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "CGameObject.h"

class Koopa;
class WalkingKoopa
{
public:
	WalkingKoopa(Koopa* k);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetCollisionBox(float x, float y) { collisionbox.x = x; collisionbox.y = y; }

	D3DXVECTOR2 GetCollisionBox();

protected:
	Koopa* koopa;
	D3DXVECTOR2 collisionbox;
	
};

