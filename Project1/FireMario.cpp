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
	int ani = MARIO_ANI_FIRE_IDLE;

	switch (mario->GetState())
	{
	case MARIO_STATE_IDLE:
		ani = MARIO_ANI_FIRE_IDLE;
		break;
	case MARIO_STATE_WALKING:
		ani = MARIO_ANI_FIRE_WALKING;
		break;
	case MARIO_STATE_RUNNING:
		ani = MARIO_ANI_FIRE_RUNNING;
		break;
	case MARIO_STATE_JUMP:
		ani = MARIO_ANI_FIRE_JUMP;
		break;
	case MARIO_STATE_SKID:
		ani = MARIO_ANI_FIRE_SKID;
		break;
	}
	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
