#pragma once
#include "CGameObject.h"
#include "Mario.h"
class MarioFireBall :
    public CGameObject
{
public:
	MarioFireBall(CMario* p);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Reset(float mx, float my);
	void Setnx(int a) { nx = a; }
	void SetActive(bool a) { active = a; }
	bool GetActive() { return active; }
protected:
	CMario* mario;
	bool active;
};

