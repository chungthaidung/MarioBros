#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "CTileset.h"
#include "CLayer.h"
#include <unordered_map>
class CMap
{
	int tilewidth, tileheight;
	int rows, columns;
	D3DCOLOR background = D3DCOLOR_XRGB(156, 252, 240);
	CTileset* tileset;
	vector<CLayer*> layers;
	std::string mapfilePath;

public:
	CMap(std::string filePath);
	void LoadGameMap();
	void Render();
	int GetTileWidth();
	int GetTileHeight();
	int GetRows();
	int GetColumns();
	D3DXVECTOR2 GetSize();
	~CMap();
	
};

