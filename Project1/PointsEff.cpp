#include "PointsEff.h"
#include "CGame.h"
#include "debug.h"
PointsEff::PointsEff(int animation):Effect()
{
	vy = -0.2;
	ani = animation;
	updatetime = 0;
}

void PointsEff::Update(DWORD dt)
{
	//DebugOut(L"delta time: %d\n", deltatime);
	if (updatetime > 400)
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	CGameObject::Update(dt);
	y += dy;
	updatetime += dt;

}

void PointsEff::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
}
