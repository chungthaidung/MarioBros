#pragma once
#include "CGameObject.h"
#include "WalkingKoopa.h"
class CMario;
class Koopa :
    public CGameObject
{
public:
	Koopa();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();

	void SetGravity(float a);
	float GetGravity();	
	D3DXVECTOR2 GetCollisionBox();
	void SetHolder(CMario* h);
	CMario* GetHolder();
	

protected:
	DWORD dietime;
	WalkingKoopa* koopaState;
	float gravity=MARIO_GRAVITY;
	CMario* holder;
};

