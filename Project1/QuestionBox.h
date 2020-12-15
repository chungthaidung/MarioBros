#pragma once
#include "CGameObject.h"
#include "define.h"

#define QUESTION_BOX_BBOX_WIDTH  48
#define QUESTION_BOX_BBOX_HEIGHT 48
#define QUESTION_BOX_ANI_REWARD		603
#define QUESTION_BOX_ANI_EMPTY		604


class QuestionBox :
    public CGameObject
{
public:
	QuestionBox(CGameObject* obj, float y = 0.0f);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt);
	virtual void CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void FinalUpdate(DWORD dt);
	virtual void SetState(int state);
	virtual int GetObjectType();
	
protected:
	float gravity = 0;
	CGameObject* reward;
	float y_start=y;
};
