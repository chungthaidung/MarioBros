#pragma once
#include "CGameObject.h"
#include "Mario.h"
class MarioTail :
    public CGameObject
{
public:
	MarioTail(CMario* p);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Moving(DWORD dt);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	void Setnx(int a) { nx = a; }
	void SetActive(bool a);
	bool GetActive() { return active; }
protected:
	CMario* mario;
	DWORD attackStart;
	bool active = 0;
};

