#include "Card.h"

Card::Card(int type, D3DXVECTOR2 pos)
{
	state = type;
	x = pos.x;
	y = pos.y;
}

void Card::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void Card::Render()
{
	int ani = MUSHROOM_CARD_ANI;
	switch (state)
	{
	case MUSHROOM:
		ani = MUSHROOM_CARD_ANI;
		break;
	case FLOWER:
		ani = FLOWER_CARD_ANI;
		break;
	case STAR:
		ani = STAR_CARD_ANI;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}
