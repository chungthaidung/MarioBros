#pragma once
#include "CGameObject.h"
#include "PlayerLevel.h"
#include "define.h"

class PlayerLevel;

class CMario : public CGameObject
{
	bool untouchable;
	DWORD untouchable_start;
	PlayerLevel* level_p;
	float start_x;			// initial position of Mario at scene
	float start_y;
	bool lockcontrol=false;
	DWORD dietime;
protected:
	float gravity;
	float ax;//gia toc
	float dragf; // luc keo
	float powerM;
	CGameObject* inHand;
public:
	bool onGround;
	bool canJumpHigh;
	bool canJumpSuper;
	int isSkid;
	bool isCrouch;
	int JumpState;
	int AttackState;
	vector<int> endgame_reward;

	bool GetUntouchable();
	DWORD GetUntouchableStart();
	bool GetLockControl();

	void SetUntouchable(bool a);
	void SetUntouchableStart(DWORD a);
	void SetLockControl(bool a);

	void SetAcceleration(float a) { ax = a; }
	void SetDrag(float d) { dragf = d; }
	void SetPowerMeter(float a) { powerM = a; }
	void SetGravity(float g) { gravity = g; }
	void SetInHand(CGameObject* obj);


	void LevelUp(CGameObject* obj);
	void LevelDown();

	float GetAcceleration() { return ax; }
	float GetDrag() { return dragf; }
	float GetPowerMeter() { return powerM; }
	float GetGravity() { return gravity; }
	CGameObject* GetInHand();
	D3DXVECTOR2 GetCollisionBox();

	int GetLevel();

	void SetState(int state);
	void SetLevel(int l);
	void StartUntouchable();
	void StopUntouchable();

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt);
	virtual void LockControlUpdate(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	virtual RECT GetBoundingBox();
	virtual int GetObjectType();

	void Reset();

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};
