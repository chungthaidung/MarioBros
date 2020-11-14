#include "CSprite.h"
#include "CGame.h"
#include "debug.h"
CSprite::CSprite(int id, RECT r, D3DXVECTOR3 p, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->sprite_r.left = r.left;
	this->sprite_r.top = r.top;
	this->sprite_r.right = r.right;
	this->sprite_r.bottom = r.bottom;
	this->texture = tex;
	this->pivot = p;
}
void CSprite::Draw(float x, float y, int scale,int flipx,int flipy, int alpha)
{
	CGame* game = CGame::GetInstance();
	D3DXVECTOR3 p = pivot;
	D3DXVECTOR2 flip(flipx, flipy);
	if (flip.x * pivot.x < 0)p.x = 0;
	if (flip.y * pivot.y < 0)p.y = 0;
	game->DrawEx(x, y, texture, sprite_r,p,scale,flip, alpha);
	
}
