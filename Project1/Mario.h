#pragma once
#include "CGameObject.h"
#include "PlayerLevel.h"
#include "define.h"

class PlayerLevel;

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	PlayerLevel* level_p;
	float start_x;			// initial position of Mario at scene
	float start_y;
protected:
	float ax;//gia toc
	float dragf; // luc keo
	float ypush;
public:
	bool onGround;
	bool canJumpHigh;
	bool isSkid;
	int JumpState;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetAcceleration(float a) { ax = a; }
	float GetAcceleration() { return ax; }
	void SetDrag(float d) { dragf = d; }
	float GetDrag() { return dragf; }
	void SetyPush(float p) { ypush = p; }
	float GetyPush() { return ypush; }


	void SetState(int state);
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	
	void Reset();

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};