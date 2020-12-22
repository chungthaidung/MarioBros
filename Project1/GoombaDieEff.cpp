#include "GoombaDieEff.h"
#include "define.h"
#include "CGame.h"
GoombaDieEff::GoombaDieEff(int animation):Effect()
{
	ny = -1;
	vy = -0.7;
	vx = 0.1;
	ani = animation;
	time = GetTickCount();
}
GoombaDieEff::GoombaDieEff(int animation, float vx, int ny) :Effect()
{
	this->ny = ny;
	this->vx = vx;
	ani = animation;
	time = GetTickCount();
}
void GoombaDieEff::Update(DWORD dt)
{
	if (y > CGame::GetInstance()->GetCamPos().y + SCREEN_HEIGHT)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	}
	vy += MARIO_GRAVITY * dt;
	CGameObject::Update(dt);
	x += dx;
	y += dy;
}

void GoombaDieEff::Render()
{
	CAnimations::GetInstance()->Get(ani)->Render(x,y,1,1,ny);
}
