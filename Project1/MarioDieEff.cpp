#include "MarioDieEff.h"
#include "CGame.h"
MarioDieEff::MarioDieEff(D3DXVECTOR2 pos)
{
	vy = -0.5;
	time = 0 ;
	gravity = 0;
	x = pos.x;
	y = pos.y;
}

void MarioDieEff::Update(DWORD dt)
{
	DWORD deltatime = CGame::DeltaTime;
	if (time > 100)
	{

		gravity = MARIO_GRAVITY;
	}
	vy += gravity * deltatime;
	CGameObject::Update(deltatime);
	x += dx;
	y += dy;
	time += deltatime;
}

void MarioDieEff::Render()
{
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(MARIO_ANI_DIE)->Render(x-cx, y-cy);
}
