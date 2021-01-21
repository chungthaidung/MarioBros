#pragma once

#define RED_KOOPA 2
#define GREEN_KOOPA 1



#define KOOPA_GRAVITY	0.002
#include "CGameObject.h"
#include "WalkingKoopa.h"
class CMario;
class Koopa :
    public CGameObject
{
public:
	Koopa(int type);
	~Koopa();
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
	D3DXVECTOR2 GetCollisionBox();
	void SetHolder(CMario* h);
	CMario* GetHolder();
	void SetType(int type);
	int GetType();

protected:
	DWORD dietime;
	WalkingKoopa* koopaState;
	float gravity=MARIO_GRAVITY;
	CMario* holder;
	int type;
};
