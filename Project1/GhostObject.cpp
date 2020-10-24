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