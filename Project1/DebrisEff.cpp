#include "DebrisEff.h"
#include "CGame.h"
DebrisEff::DebrisEff(int type)
{
	start_pos = type;
	switch (start_pos)
	{
	case LEFT_TOP:
		vx = -0.1;
		vy = -0.7;
		break;
	case RIGHT_TOP:	
		vx = 0.1;
		vy = -0.7;
		break;
	case LEFT_BOTTOM:
		vx = -0.1;
		vy = -0.5;
		break;
	case RIGHT_BOTTOM:
		vx = 0.1;
		vy = -0.5;
		break;

	}
}

void DebrisEff::SetPosition(float x, float y)
{
	switch (start_pos)
	{
	case LEFT_TOP:
		this->x = x;
		this->y = y;
		break;
	case RIGHT_TOP:
		this->x = x+ BRICK_BBOX_WIDTH;
		this->y = y;
		break;
	case LEFT_BOTTOM:
		this->x = x;
		this->y = y+ BRICK_BBOX_HEIGHT;
		break;
	case RIGHT_BOTTOM:
		this->x = x + BRICK_BBOX_WIDTH;
		this->y = y + BRICK_BBOX_HEIGHT;
		break;
	}
}

void DebrisEff::Update(DWORD dt)
{
	if(y>CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y + CGame::GetInstance()->GetScreenHeight())
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	vy += MARIO_GRAVITY*dt;
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}
void DebrisEff::Render()
{
	int ani = DEBRIS_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
}
