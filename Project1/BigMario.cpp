#include "BigMario.h"


BigMario::BigMario(CMario* mario) :PlayerLevel(mario)
{
}
void BigMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + MARIO_BIG_BBOX_WIDTH;
	bottom = top + MARIO_BIG_BBOX_HEIGHT;
}
void BigMario::Render()
{
	int ani = -1;
	if (mario->vx == 0)
	{
		//if (mario->nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
		 ani = MARIO_ANI_BIG_IDLE_LEFT;
	}
	else //if (mario->vx > 0)
		ani = MARIO_ANI_BIG_WALKING_RIGHT;
	//else ani = MARIO_ANI_BIG_WALKING_LEFT;
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
