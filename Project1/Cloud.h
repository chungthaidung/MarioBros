#pragma once
#include "CGameObject.h"

#define CLOUD_BBOX_WIDTH 48
#define CLOUD_BBOX_HEIGHT 48

class Cloud :public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

