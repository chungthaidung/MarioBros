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
	int ani = MARIO_ANI_BIG_IDLE;

	switch (mario->GetState())
	{
	case MARIO_STATE_IDLE:
		ani = MARIO_ANI_BIG_IDLE;
		break;
	case MARIO_STATE_WALKING:
		ani = MARIO_ANI_BIG_WALKING;
		break;
	case MARIO_STATE_RUNNING:
		ani = MARIO_ANI_BIG_RUNNING;
		break;
	case MARIO_STATE_JUMP:
		ani = MARIO_ANI_BIG_JUMP;
		break;
	case MARIO_STATE_SKID:
		ani = MARIO_ANI_BIG_SKID;
		break;
	}
	int alpha = 255;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
