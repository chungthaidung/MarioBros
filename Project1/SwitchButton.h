#pragma once
#include "CGameObject.h"
#define SWITCH_BUTTON_ANI_UP   613
#define SWITCH_BUTTON_ANI_DOWN  614

#define SWITCH_BUTTON_BBOX_WIDTH   48
#define SWITCH_BUTTON_BBOX_HEIGHT   48

#define SWITCH_BUTTON_STATE_UP 1
#define SWITCH_BUTTON_STATE_DOWN	2
class SwitchButton :
    public CGameObject
{
public:
    SwitchButton();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	virtual void SetState(int state);
	virtual int GetObjectType();
protected:

	vector<CGameObject*> bricks;
	DWORD time;
	D3DXVECTOR2 collisionbox;
};

