#include "RacoonMario.h"



RacoonMario::RacoonMario(CMario* mario) :PlayerLevel(mario)
{
}
void RacoonMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + MARIO_RACOON_BBOX_WIDTH;
	bottom = top + MARIO_RACOON_BBOX_HEIGHT;
}
void RacoonMario::Render()
{
	int ani = -1;
	if (mario->vx == 0)
	{
		//if (mario->nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
		ani = MARIO_ANI_RACOON_IDLE;
	}
	else
		ani = MARIO_ANI_RACOON_WALKING;

		
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
