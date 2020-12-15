#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Utils.h"
#include "CTileset.h"
#include <unordered_map>
class CLayer
{
	int tile[500][500];
	int layer_columns, layer_rows;
	int id, visible;
public: 
	CLayer(TiXmlElement* data);
	void SetVisible(int set);
	int isVisible();
	void Draw(float cam_x,float cam_y,CTileset* tileset);
	~CLayer();
};

