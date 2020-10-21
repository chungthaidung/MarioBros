#include "Cloud.h"
void Cloud::Render()
{
	animation_set->at(1)->Render(x, y);
	RenderBoundingBox();
}

void Cloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CLOUD_BBOX_WIDTH;
	b = y + CLOUD_BBOX_HEIGHT;
}