#pragma once
#include "PlayerLevel.h"
#include "MarioFireBall.h"
class FireMario:public PlayerLevel
{
public:
	FireMario(CMario* mario);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void CrouchState(DWORD dt);
	virtual void AttackState(DWORD dt);
	virtual void OnKeyDown(int KeyCode);
	virtual int GetPlayerLevel();
	bool IsActive();
	void AttackStart();
protected:
	DWORD attacktime;
	vector<MarioFireBall*> fireballs;
};

