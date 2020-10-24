#pragma once
#include "PlayerLevel.h"
class RacoonMario:public PlayerLevel
{
public:
	RacoonMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

