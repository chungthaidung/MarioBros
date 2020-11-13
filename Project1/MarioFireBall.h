#pragma once
#include "CGameObject.h"
#include "Mario.h"
class MarioFireBall :
    public CGameObject
{
public:
	MarioFireBall(CMario* p);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Reset(float mx, float my);
	virtual int GetObjectType();
	void State(DWORD dt);
	
	void SetActive(bool a) { active = a; }
	bool GetActive() { return active; }
protected:
	CMario* mario;
	bool active;
	DWORD damagedtime;
	float gravity= FIREBALL_GRAVITY;
};

