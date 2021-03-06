#include "Effect.h"
#include "define.h"
Effect::Effect()
{
	canDelete = true;
	isRemove = false;
	renderOrder = 200;
}

void Effect::Update(DWORD dt)
{
}

void Effect::Render()
{
}

void Effect::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x;
	bottom = y;
}

bool Effect::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	return true;
}

int Effect::GetObjectType()
{
	return OBJECT_TYPE_EFFECT;
}
