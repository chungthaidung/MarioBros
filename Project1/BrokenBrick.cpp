#include "BrokenBrick.h"
#include "Brick.h"
#include "CGameObject.h"
BrokenBrick::BrokenBrick(Brick* obj)
{
	brick = obj;
	x = brick->x;
	y = brick->y;
	vx = 0.1;
	vy = brick->vy;

}

BrokenBrick::~BrokenBrick()
{
}

void BrokenBrick::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	vy += MARIO_GRAVITY * dt;
}

void BrokenBrick::Render()
{
	int ani = BRICK_ANI_BROKEN;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
