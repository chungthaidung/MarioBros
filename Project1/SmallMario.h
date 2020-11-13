#pragma once
#include "PlayerLevel.h"
class SmallMario :public PlayerLevel
{
public:
	SmallMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetPlayerLevel();
};

