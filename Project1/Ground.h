#pragma once
#include "CGameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48

class CGround : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
};