#include "EndGameRewardEff.h"
#include "CGame.h"
EndGameRewardEff::EndGameRewardEff(int ani)
{
	this->ani = ani;
	vy = -0.5;
}
void EndGameRewardEff::Update(DWORD dt)
{
	if (y < CGame::GetInstance()->GetCamPos().y )
	{
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	}
	CGameObject::Update(dt);
	y += dy;
}
void EndGameRewardEff::Render()
{
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
