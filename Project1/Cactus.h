#pragma once
#include "CGameObject.h"
#define CACTUS_ANI 1517
class Cactus :
    public CGameObject
{
public:
	Cactus();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
};

