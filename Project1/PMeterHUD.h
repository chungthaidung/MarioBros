#pragma once
#include "Mario.h"
#define PMETER_HUD_POSITION_X 171
#define PMETER_HUD_POSITION_Y	52
#define PMETER_BUTTON_HUD_POSITION_x	308
#define PMETER_X_DISTANCE 22
#define PMETER_WHITE_POINTER_ANI 1511
#define PMETER_MAX_BUTTON_ANI 1512

class PMeterHUD
{
public:
	PMeterHUD();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void SetTarget(CMario* mario);
	virtual CMario* GetTarget();
protected:
	int state;
	float x, y;
	CMario* target;
};

