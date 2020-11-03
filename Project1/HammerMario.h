#pragma once
#include "PlayerLevel.h"
class HammerMario:public PlayerLevel
{
public:
	HammerMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CrouchState(DWORD dt);


};

