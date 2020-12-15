#pragma once
#include "CGameObject.h"
#define PIRANHA_BBOX_WIDTH 48
#define PIRANHA_BBOX_HEIGHT 72

#define PIRANHA_STATE_UP 1
#define PIRANHA_STATE_DOWN 2
#define PIRANHA_STATE_STAY 3
class Piranha :
    public CGameObject
{
public:
	Piranha(int t,float start_y);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	int GetType();
protected:
	int type;
	float y_start;
	DWORD staytime;
};

