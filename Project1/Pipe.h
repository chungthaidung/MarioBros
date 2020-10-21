#pragma once
#include "CGameObject.h"

#define PIPE_BBOX_WIDTH  96
#define PIPE_BBOX_HEIGHT 48
class Pipe : public CGameObject
{
protected:

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

