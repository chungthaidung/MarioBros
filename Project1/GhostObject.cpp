#include "GhostObject.h"
void GhostObject::Render()
{
	RenderBoundingBox();
}
void GhostObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

int GhostObject::GetObjectType()
{
	return OBJECT_TYPE_GHOST;
}

bool GhostObject::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	return false;
}
