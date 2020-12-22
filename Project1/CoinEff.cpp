#include "CoinEff.h"
#include "CGame.h"
#include "debug.h"
CoinEff::CoinEff():Effect()
{
	vy = -0.5;
	time = GetTickCount();
}

void CoinEff::Update(DWORD dt)
{
	if (y < y_start - 144) {
		y = y_start - 144;
		vy = 0.5;
	}
	else if (y > y_start)
	{
		y = y_start;
	}
	if(GetTickCount()-time>500 && vy>0)
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	CGameObject::Update(dt);
	y += dy;
	//DebugOut(L"[COIN EFFECT INFO]y: %f\n", y);
}

void CoinEff::Render()
{
	CAnimations::GetInstance()->Get(COIN_EFFECT_ANI)->Render(x,y);
}

void CoinEff::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	y_start = y;
	//DebugOut(L"[COIN EFFECT INFO]y start: %f\n", y_start);

}
