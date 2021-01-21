#pragma once
#include "PlayerLevel.h"
#include "MarioTail.h"
class RacoonMario:public PlayerLevel
{
public:
	~RacoonMario();
	RacoonMario(CMario* mario);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void AttackState(DWORD dt);
	virtual void PowerMeterUpdate(DWORD dt);
	virtual void JumpingState(DWORD dt);
	virtual void MiniJump(bool isJump=false);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual int GetPlayerLevel();
	virtual MarioTail* GetMarioWeapon();
protected:
	DWORD flytime;
	DWORD attacktime;
	MarioTail* tail;
	int flyflag;
	
};

