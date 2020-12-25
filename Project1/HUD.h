#pragma once
#include "Mario.h"
#include "PMeterHUD.h"
#define HUD_ANI 1509
#define CARD_ANI	1510
#define HUD_POSITION_X 10
#define HUD_POSITION_Y	30
class HUD
{
public:
	HUD();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void SetTarget(CMario* mario);
	virtual CMario* GetTarget();
protected:
	float x, y;
	CMario* target;
	PMeterHUD* pmeter;
};

