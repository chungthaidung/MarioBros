#pragma once
#include "CGameObject.h"
#include "VenusFireBall.h"
#define VENUS_BBOX_WIDTH 48
#define VENUS_BBOX_HEIGHT 96

#define VENUS_STATE_UP 1
#define VENUS_STATE_DOWN 2
#define VENUS_STATE_IDLE	3

#define VENUS_HEAD_UP	5
#define VENUS_HEAD_DOWN	6

#define GREEN_VENUS_ANI_HEAD_DOWN_IDLE	1019
#define GREEN_VENUS_ANI_HEAD_UP_IDLE	1020
#define GREEN_VENUS_ANI_HEAD_DOWN	1021
#define GREEN_VENUS_ANI_HEAD_UP	1022

#define RED_VENUS_ANI_HEAD_DOWN_IDLE	1023
#define RED_VENUS_ANI_HEAD_UP_IDLE	1024
#define RED_VENUS_ANI_HEAD_DOWN	1025
#define RED_VENUS_ANI_HEAD_UP	1026
class Venus :
    public CGameObject
{
public:
	Venus(int t, int ny,float start_y);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual int GetObjectType();
	virtual void Attack();
	int GetType();
	int GetHead();
	D3DXVECTOR2 GetCollisionBox();
protected:
	int type,head;
	float y_start;
	DWORD staytime;
	VenusFireBall* fireball;
};

