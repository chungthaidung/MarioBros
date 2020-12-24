#pragma once
#include "CGameObject.h"
#define SUPER_MUSHROOM_BBOX_WIDTH 48
#define SUPER_MUSHROOM_BBOX_HEIGHT 48

#define SUPER_MUSHROOM_VELOCITY 0.2f

#define SUPER_MUSHROOM_STATE_UP 1
#define SUPER_MUSHROOM_STATE_MOVE 2

#define SUPER_MUSHROOM_ANI	611
class SuperMushroom :
    public CGameObject
{
public:
    SuperMushroom(float y_s);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	void SetGravity(float g);
protected:
	float gravity;
	float y_start;
};

