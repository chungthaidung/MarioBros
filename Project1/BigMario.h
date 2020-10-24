#pragma once
#include "PlayerLevel.h"
class BigMario :public PlayerLevel
{
public:
	BigMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	
};

