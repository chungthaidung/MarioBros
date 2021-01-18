#pragma once
#include "CGameObject.h"
#define MARIO_WORLD_ANI_SMALL	316
#define MARIO_WORLD_ANI_BIG	317
#define MARIO_WORLD_ANI_RACOON	318
#define MARIO_WORLD_ANI_FIRE	319

#define MARIO_WORLD_BBOX_WIDTH 48
#define MARIO_WORLD_BBOX_HEIGHT 48
class WorldMario :
    public CGameObject
{
protected:
    int level_p;
public:
	WorldMario();
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	void SetLevel(int level);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

