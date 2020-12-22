#include "SwitchButtonEff.h"

SwitchButtonEff::SwitchButtonEff():Effect()
{
}

void SwitchButtonEff::Update(DWORD dt)
{
}

void SwitchButtonEff::Render()
{
	int ani = SWITCH_BUTTON_ANI_DOWN;
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
