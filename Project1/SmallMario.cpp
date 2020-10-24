#include "SmallMario.h"

SmallMario::SmallMario(CMario* mario):PlayerLevel(mario)
{
}
void SmallMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left,top);
	right = left + MARIO_SMALL_BBOX_WIDTH;
	bottom = top + MARIO_SMALL_BBOX_HEIGHT;
}
void SmallMario::Render()
{
	int ani = -1;
	if (mario->vx == 0)
	{
		if (mario->nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
		else ani = MARIO_ANI_SMALL_IDLE_LEFT;
	}
	else if (mario->vx > 0)
		ani = MARIO_ANI_SMALL_WALKING_RIGHT;
	else ani = MARIO_ANI_SMALL_WALKING_LEFT;
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}

