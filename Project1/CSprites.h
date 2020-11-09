#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "CSprite.h"

// Manage sprite database

class CSprites
{
	static CSprites* __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, RECT r, D3DXVECTOR3 p, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int id);
	void Clear();
	static CSprites* GetInstance();
};

