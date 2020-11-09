#include "CSprites.h"
#include "CGame.h"
#include "debug.h"

#include "CSprite.h"
CSprites* CSprites::__instance = NULL;

CSprites* CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}



void CSprites::Add(int id, RECT r, D3DXVECTOR3 p, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, r,p, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}
	sprites.clear();
}

