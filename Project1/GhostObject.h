#pragma once
#include "CGameObject.h"


class GhostObject :public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
};




