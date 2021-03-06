#include "FireBallEf.h"
#include "CGame.h"

FireBallEf::FireBallEf():Effect()
{
	time = GetTickCount();
}

void FireBallEf::Update(DWORD dt)
{
	if (GetTickCount() - time > 120)
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
}

void FireBallEf::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	int ani = FIREBALL_DAMAGED_EFFECT_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy, time, 120);
}
