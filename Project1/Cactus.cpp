#include "Cactus.h"

Cactus::Cactus():CGameObject()
{

}

void Cactus::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void Cactus::Render()
{
	CAnimations::GetInstance()->Get(CACTUS_ANI)->Render(x, y);
}

void Cactus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x;
	bottom = y;

}

int Cactus::GetObjectType()
{
	return OBJECT_TYPE_CACTUS;
}
