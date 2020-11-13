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
	float gravity;
	float ax;//gia toc
	float dragf; // luc keo
	float ypush;
	float powerM;
public:
	bool onGround;
	bool canJumpHigh;
	bool canJumpSuper;
	bool isSkid;
	bool isCrouch;
	int JumpState;
	int AttackState;

	void SetAcceleration(float a) { ax = a; }
	void SetDrag(float d) { dragf = d; }
	void SetyPush(float p) { ypush = p; }
	void SetPowerMeter(float a) { powerM = a; }
	void SetGravity(float g) { gravity = g; }
	void Setnx(float n) { nx = n;}
	
	float GetAcceleration() { return ax; }
	float GetDrag() { return dragf; }
	float GetyPush() { return ypush; }
	float GetPowerMeter() { return powerM; }
	float GetGravity() { return gravity; }
	float Getnx() { return nx; }

	void SetState(int state);
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetObjectType();

	void Reset();

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};