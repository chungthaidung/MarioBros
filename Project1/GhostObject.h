#pragma once
#include "CGameObject.h"

#define GHOSTOBJ_BBOX_WIDTH 48
#define GHOSTOBJ_BBOX_HEIGHT 48
class GhostObject:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

