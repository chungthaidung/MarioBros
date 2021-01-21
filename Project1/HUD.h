#pragma once
#include "Mario.h"
#include "PMeterHUD.h"
#include "Font.h"
#define HUD_ANI 1509
#define CARD_ANI	1510

#define MUSHROOM	1
#define FLOWER	2
#define STAR	3

#define CARD_DISTANCE_X	9

#define CARD_POSITION_X 490
#define CARD_POSITION_Y 30

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
	D3DXVECTOR2 hudposition;
	D3DXVECTOR2 cardposition;
	CMario* target;
	PMeterHUD* pmeter;
	Font* time;
	Font* life;
	Font* stageclear;
	Font* points;
};

