#include "FireMario.h"
#include "CGame.h"

FireMario::FireMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_FIRE_BBOX_WIDTH;
	collisionbox.y = MARIO_FIRE_BBOX_HEIGHT;
}
void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
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
void FireMario::CrouchState(DWORD dt)
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
		collisionbox.y = MARIO_FIRE_BBOX_HEIGHT;
	}
	mario->SetPosition(x, y - collisionbox.y);
}