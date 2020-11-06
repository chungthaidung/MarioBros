#pragma once
#include "PlayerLevel.h"
#include "MarioFireBall.h"
class FireMario:public PlayerLevel
{
public:
	FireMario(CMario* mario);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CrouchState(DWORD dt);
	virtual void AttackState(DWORD dt);
	virtual void OnKeyDown(int KeyCode);
	virtual bool IsActive();
	virtual void AttackStart(DWORD dt);
protected:
	DWORD attacktime;
	vector<MarioFireBall*> fireballs;
	int ballnumber;
};

