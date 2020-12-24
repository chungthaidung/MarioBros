#pragma once
#include "Mario.h"
#define HUD_ANI 1509
#define CARD_ANI	1510
class HUD
{
public:
	HUD();
	virtual void Update(DWORD dt);
	virtual void Render();
protected:
	CMario* target;
};

