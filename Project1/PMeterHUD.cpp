#include "PMeterHUD.h"
#include "debug.h"
PMeterHUD::PMeterHUD()
{
	x = PMETER_HUD_POSITION_X;
	y = PMETER_HUD_POSITION_Y;
}

void PMeterHUD::Update(DWORD dt)
{
	if (target != NULL)
	{
		state = (int)target->GetPowerMeter();
		//DebugOut(L"Power Meter: %d\n", state);

	}
}

void PMeterHUD::Render()
{
	for (int i = 0; i < state; i++)
	{
		if (i<6)
		CAnimations::GetInstance()->Get(PMETER_WHITE_POINTER_ANI)->Render(x	+ i* PMETER_X_DISTANCE, y);
	}
	if (state == 7)
		CAnimations::GetInstance()->Get(PMETER_MAX_BUTTON_ANI)->Render(PMETER_BUTTON_HUD_POSITION_x, y);
}

void PMeterHUD::SetTarget(CMario* mario)
{
	if(mario!=NULL)
		target = mario;
}

CMario* PMeterHUD::GetTarget()
{
	return target;
}
