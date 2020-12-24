#pragma once
#include "CGameObject.h"

class SuperLeaf :
    public CGameObject
{
public:
    SuperLeaf(float x_s,float y_s);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	virtual void SetPosition(float x, float y);
	void SetGravity(float g);
	void SetXStart(float x_s);
protected:
	float gravity;
	float x_start,y_start;
};

