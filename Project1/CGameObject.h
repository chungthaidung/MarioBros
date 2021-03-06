#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "CSprites.h"
#include "CAnimation.h"
#include "CKeyEventHandler.h"

#include "CAnimationSets.h"
#include "define.h"
#include "CCollisionEvent.h"

using namespace std;
	

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float width;
	float height;

	float vx;
	float vy;


	int nx;
	int ny = 1;

	int state;
	bool isEnemy = false;
	bool isRemove;
	DWORD dt;

	bool canDelete = true;

	int renderOrder=50;

	LPANIMATION_SET animation_set;
	vector<LPCOLLISIONEVENT> coEResult;
public:

	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	D3DXVECTOR2 GetPosition();
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	virtual void SetWidthHeight(int w, int h) { width = w; height = h; }
	int GetState() { return this->state; }
	void Setnx(float n) { nx = n; }
	int Getnx() { return nx; }
	void Setny(int a);
	int Getny();
	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	static bool rendercompare(CGameObject*& a, CGameObject*& b);
	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction) = 0;
	virtual D3DXVECTOR2 GetWidthHeight();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render() = 0;
	virtual void SetState(int state);
	virtual int GetObjectType() = 0;

	~CGameObject();
};