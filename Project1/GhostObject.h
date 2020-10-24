#pragma once
#include "CGameObject.h"


class GhostObject:public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

