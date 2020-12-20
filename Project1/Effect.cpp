#include "Effect.h"
#include "define.h"
Effect::Effect()
{
	canDelete = true;
	isRemove = false;
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

int Effect::GetObjectType()
{
	return OBJECT_TYPE_EFFECT;
}
