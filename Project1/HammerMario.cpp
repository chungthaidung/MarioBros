#include "HammerMario.h"
#include "CGame.h"

HammerMario::HammerMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_HAMMER_BBOX_WIDTH;
	collisionbox.y = MARIO_HAMMER_BBOX_HEIGHT;
}
void HammerMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void HammerMario::Render()
{
	int ani = MARIO_ANI_HAMMER_IDLE;
	if (mario->isCrouch == true)
	{
		ani = MARIO_ANI_HAMMER_CROUCH;
	}
	else if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_HAMMER_JUMP;
			break;
		case MARIO_STATE_FALL:
			ani = MARIO_ANI_HAMMER_FALL;
			break;
		}
	}
	else {
		switch (mario->GetState())
		{
		case MARIO_STATE_IDLE:
			ani = MARIO_ANI_HAMMER_IDLE;
			break;
		case MARIO_STATE_WALKING:
			ani = MARIO_ANI_HAMMER_WALKING;
			break;
		case MARIO_STATE_RUNNING:
			ani = MARIO_ANI_HAMMER_RUNNING;
			break;
		case MARIO_STATE_JUMP:
			ani = MARIO_ANI_HAMMER_JUMP;
			break;
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_HAMMER_SKID;
			break;
		}
	}

	int alpha = 255;
	//if (mario->untouchable) alpha = 128;
	CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx, alpha);
	mario->RenderBoundingBox();
}
void HammerMario::CrouchState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	float x, y;
	mario->GetPosition(x, y);
	y += collisionbox.y;
	if (mario->state == MARIO_STATE_IDLE && keyboard->IsKeyDown(DIK_DOWN))
	{
		mario->isCrouch = true;
		collisionbox.y = MARIO_CROUCH_BBOX_HEIGHT;
	}
	else
	{
		mario->isCrouch = false;
		collisionbox.y = MARIO_HAMMER_BBOX_HEIGHT;
	}
	mario->SetPosition(x, y - collisionbox.y);
}

