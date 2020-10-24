#pragma once
#include "CGameObject.h"
#include "PlayerLevel.h"
#include "define.h"

class PlayerLevel;

class CMario : public CGameObject
{
protected:
	int level;
	int untouchable;
	DWORD untouchable_start;
	PlayerLevel* level_p;
	float start_x;			// initial position of Mario at scene
	float start_y;
	
public:
	bool onGround ;
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};