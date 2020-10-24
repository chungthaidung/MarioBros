#pragma once
#include "PlayerLevel.h"
class FireMario:public PlayerLevel
{
public:
	FireMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

