#include "CoinEff.h"
#include "CGame.h"
#include "debug.h"
#include "PointsEff.h"
#include "define.h"
CoinEff::CoinEff():Effect()
{
	vy = -0.5;
	time = GetTickCount();
}

CoinEff::~CoinEff()
{
	
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
	if(GetTickCount()-time>500 && vy>0){
		PointsEff* eff = new PointsEff(POINT_100_ANI);
		eff->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);
	}
	CGameObject::Update(dt);
	y += dy;
	//DebugOut(L"[COIN EFFECT INFO]y: %f\n", y);
}

void CoinEff::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(COIN_EFFECT_ANI)->Render(x-cx,y-cy);
}

void CoinEff::SetPosition(float x, float y)
{
	CGameObject::SetPosition(x, y);
	y_start = y;
	//DebugOut(L"[COIN EFFECT INFO]y start: %f\n", y_start);

}
