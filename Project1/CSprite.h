#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	RECT sprite_r;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 pivot;
public:
	CSprite(int id, RECT r, D3DXVECTOR3 p, LPDIRECT3DTEXTURE9 tex);
	
	void Draw(float x, float y,int scale=1, int flipx=1, int alpha = 255);
};

typedef CSprite* LPSPRITE;

