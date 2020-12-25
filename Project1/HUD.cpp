#include "HUD.h"

HUD::HUD()
{
	pmeter = new PMeterHUD();
	x = HUD_POSITION_X;
	y = HUD_POSITION_Y;
}

void HUD::Update(DWORD dt)
{
	pmeter->Update(dt);
}

void HUD::Render()
{
	int ani = HUD_ANI;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	pmeter->Render();
}

void HUD::SetTarget(CMario* mario)
{
	if (mario != NULL)
	{
		target = mario;
		pmeter->SetTarget(mario);

	}
}

CMario* HUD::GetTarget()
{
	return target;
}
