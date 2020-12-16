#include "SuperMushroom.h"
#include "define.h"

SuperMushroom::SuperMushroom():CGameObject()
{
}

void SuperMushroom::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void SuperMushroom::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void SuperMushroom::FinalUpdate(DWORD dt)
{
}

void SuperMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	
}

void SuperMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + SUPER_MUSHROOM_BBOX_WIDTH;
	bottom = y + SUPER_MUSHROOM_BBOX_HEIGHT;
}

void SuperMushroom::Render()
{
	int ani = SUPER_MUSHROOM_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}

int SuperMushroom::GetObjectType()
{
	return OBJECT_TYPE_SUPER_MUSHROOM;
}

void SuperMushroom::SetGravity(float g)
{
	gravity = g;
}
