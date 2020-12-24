#include "TailAttackEf.h"
#include "CGame.h"
#include "debug.h"
TailAttackEf::TailAttackEf()
{
	time = GetTickCount();
}

void TailAttackEf::Update(DWORD dt)
{
	if (GetTickCount() - time > 249)		
		CGame::GetInstance()->GetCurrentScene()->DeleteEffect(this);

}

void TailAttackEf::Render()
{
	int ani = TAIL_ATTACK_EFFECT_ANI;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy, time, 250); //
}
