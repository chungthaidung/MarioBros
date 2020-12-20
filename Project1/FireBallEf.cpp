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
	int ani = FIREBALL_DAMAGED_EFFECT_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y, time, 120);
}
