#include "Ground.h"

void CGround::Render()
{
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

int CGround::GetObjectType()
{
	return OBJECT_TYPE_GROUND;
}

bool CGround::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	return false;
}
