#include "SmallMario.h"

SmallMario::SmallMario(CMario* mario):PlayerLevel(mario)
{
	collisionbox.x = MARIO_SMALL_BBOX_WIDTH;
	collisionbox.y = MARIO_SMALL_BBOX_HEIGHT;

}
void SmallMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left,top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void SmallMario::CrouchState(DWORD dt)
{
}
int SmallMario::GetPlayerLevel()
{
	return MARIO_LEVEL_SMALL;
}
void SmallMario::Render()
{
	int ani = MARIO_ANI_SMALL_IDLE;
	int f = 1;
	if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_FALL:
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_SMALL_JUMP;
			break;
		case MARIO_STATE_SUPER_JUMP:
		case MARIO_STATE_SUPER_FALL:
			ani = MARIO_ANI_SMALL_SUPER_JUMP;
			break;

		}
		if (mario->GetInHand() != NULL)
		{
			ani = MARIO_ANI_SMALL_HOLD_FALL;
		}
	}
	else {
		switch (mario->GetState())
		{
		case MARIO_STATE_IDLE:
			ani = MARIO_ANI_SMALL_IDLE;
			break;
		case MARIO_STATE_WALKING:
			ani = MARIO_ANI_SMALL_WALKING;
			break;
		case MARIO_STATE_RUNNING:
			ani = MARIO_ANI_SMALL_RUNNING;
			break;
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_SMALL_SKID;
			f = -1;
			break;
		}
		if (mario->GetInHand() != NULL && mario->GetState()== MARIO_STATE_IDLE)
			ani = MARIO_ANI_SMALL_HOLD_IDLE;
		else if (mario->GetInHand() != NULL)
			ani = MARIO_ANI_SMALL_HOLD;
	}

	int alpha = 255;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx*f,1, alpha);
	mario->RenderBoundingBox();
}

