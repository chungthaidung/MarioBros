#pragma once
#include "CGameObject.h"
#include "define.h"


class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


public:
	CGoomba();
	virtual void SetState(int state);
};