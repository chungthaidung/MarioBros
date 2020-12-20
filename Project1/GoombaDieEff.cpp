#include "GoombaDieEff.h"
#include "define.h"
#include "CGame.h"
GoombaDieEff::GoombaDieEff(int animation):Effect()
{
	ny = -1;
	vy = -0.7;
	ani = animation;
	time = GetTickCount();
}
GoombaDieEff::GoombaDieEff(int animation, float vy, int ny) :Effect()
{
	this->ny = ny;
	this->vy = vy;
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
	CAnimations::GetInstance()->Get(ani)->Render(x,y,1,nx,ny);
}
