#include "EndGameRewardEff.h"
#include "CGame.h"
EndGameRewardEff::EndGameRewardEff(int ani)
{
	this->ani = ani;
	vy = -0.5;
}
void EndGameRewardEff::Update(DWORD dt)
{
	if (y < CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y)
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	}
	CGameObject::Update(dt);
	y += dy;
}
void EndGameRewardEff::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
}
