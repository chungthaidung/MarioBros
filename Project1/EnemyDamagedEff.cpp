#include "EnemyDamagedEff.h"
#include "CGame.h"
EnemyDamagedEff::EnemyDamagedEff()
{
	time = GetTickCount();
}

void EnemyDamagedEff::Update(DWORD dt)
{
	if(GetTickCount()-time>250)
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
}

void EnemyDamagedEff::Render()
{
	int ani = ENEMY_DAMAGED_EFFECT_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy,time,250);
}
