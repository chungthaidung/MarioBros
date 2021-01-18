#pragma once
#include "CGameObject.h"
#include "NormalGoomba.h"
#define RED_GOOMBA_ANI_WALKING 1011
#define RED_GOOMBA_ANI_DIE 1012
#define RED_GOOMBA_FLY_ANI_WALK 1013
#define RED_GOOMBA_FLY_ANI_FLY 1014
#define GOOMBA_FLY_ANI_WALK 1015
#define GOOMBA_FLY_ANI_FLY 1016
#define GOOMBA_GRAVITY	0.002

class Goomba :
    public CGameObject
{
public:
	Goomba(int type);

	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	int GetType();
	DWORD GetDieTime();
	void SetDieTime(DWORD time);
protected:
	DWORD dietime;
	D3DXVECTOR2 collision_box;
	int type;
	NormalGoomba* goombaState;
};

