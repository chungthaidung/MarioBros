#include "BigMario.h"
#include "CGame.h"

BigMario::BigMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_BIG_BBOX_WIDTH;
	collisionbox.y = MARIO_BIG_BBOX_HEIGHT;

}
void BigMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}

void BigMario::Render()
{
	int ani = MARIO_ANI_BIG_IDLE;
	if (mario->GetState() == MARIO_STATE_CROUCH)
	{
		ani = MARIO_ANI_BIG_CROUCH;
	}
	else if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_BIG_JUMP;
			break;
		case MARIO_STATE_SUPER_JUMP:
		case MARIO_STATE_SUPER_FALL:
			ani = MARIO_ANI_BIG_SUPER_JUMP;
			break;
		case MARIO_STATE_FALL:
			ani = MARIO_ANI_BIG_FALL;
			break;
		}
	}
	else {
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
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_BIG_SKID;
			break;
		case MARIO_STATE_CROUCH:
			ani = MARIO_ANI_BIG_CROUCH;

			break;
		}
	}
	int alpha = 255;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}


int BigMario::GetPlayerLevel()
{
	return 2;
}
