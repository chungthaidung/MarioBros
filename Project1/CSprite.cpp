#include "CSprite.h"
#include "CGame.h"
#include "debug.h"
CSprite::CSprite(int id, RECT r, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->sprite_r.left = r.left;
	this->sprite_r.top = r.top;
	this->sprite_r.right = r.right;
	this->sprite_r.bottom = r.bottom;
	this->texture = tex;
}
void CSprite::Draw(float x, float y, int scale, int flipx, int alpha)
{
	CGame* game = CGame::GetInstance();
	game->DrawEx(x, y, texture, sprite_r,scale,flipx, alpha);
	
}
