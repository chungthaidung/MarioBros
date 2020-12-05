#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CTextures.h"
#include "CGame.h"
#include "CSprite.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
class CTileset
{
	int firstgid;
	int tilewidth, tileheight;
	int rows, columns;
	LPDIRECT3DTEXTURE9 texture;
	vector<LPSPRITE> tiles;
public:
	CTileset(TiXmlElement* data);
	void AddTiles();
	void Draw(int id, float cam_x,float cam_y);
	int GetTileWidth();
	int GetTileHeight();
};

