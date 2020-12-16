#pragma once
#include "CGameObject.h"

#define VENUS_FIRE_BALL_BBOX_WIDTH 24
#define VENUS_FIRE_BALL_BBOX_HEIGHT 24

#define VENUS_FIRE_BALL_ANI	500

#define VENUS_FIRE_BALL_VELOCITY	0.1
class Venus;
class VenusFireBall :
    public CGameObject
{
public:
	VenusFireBall(Venus* v);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Reset(float start_x, float start_y, float mx, float my);
	virtual int GetObjectType();
	void SetActive(bool a);
	bool GetActive();
protected:
	Venus* venus;
	bool active;
};

