#pragma once
#include "PlayerLevel.h"
class RacoonMario:public PlayerLevel
{
public:
	RacoonMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CrouchState(DWORD dt);
	virtual void AttackState(DWORD dt);
	virtual void PowerMeterUpdate(DWORD dt);
	virtual void JumpingState(DWORD dt);
	virtual void MiniJump(DWORD dt);
	virtual void OnKeyDown(int KeyCode);
protected:
	DWORD flytime;
	DWORD attacktime;
};

