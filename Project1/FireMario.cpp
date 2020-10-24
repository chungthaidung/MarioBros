#include "FireMario.h"


FireMario::FireMario(CMario* mario) :PlayerLevel(mario)
{
}
void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + MARIO_FIRE_BBOX_WIDTH;
	bottom = top + MARIO_FIRE_BBOX_HEIGHT;
}
void FireMario::Render()
{
	int ani = -1;
	if (mario->vx == 0)
	{
		ani = MARIO_ANI_FIRE_IDLE;
	}
	else 
		ani = MARIO_ANI_FIRE_WALKING;
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
