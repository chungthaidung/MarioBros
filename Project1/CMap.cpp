#include "CMap.h"
#include "CGame.h"
#include "Utils.h"
#include "debug.h"
CMap::CMap(std::string filePath)
{
	mapfilePath = filePath;
}

void CMap::LoadGameMap()
{
	//TiXmlDocument doc("world-1-1-map.tmx");
	TiXmlDocument doc(mapfilePath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		root->QueryIntAttribute("width", &columns);
		root->QueryIntAttribute("height", &rows);
		root->QueryIntAttribute("tilewidth", &tilewidth);
		root->QueryIntAttribute("tileheight", &tileheight);
		tileset = new CTileset(root->FirstChildElement("tileset"));
		//tileset->AddTiles();
		for(TiXmlElement* datalayer = root->FirstChildElement("layer");datalayer!=NULL; datalayer = datalayer->NextSiblingElement("layer"))
		{
			CLayer* layer= new CLayer(datalayer);
			layers.push_back(layer);
		}
		DebugOut(L"[INFO]Load map successful. \n");
	}
	else
		DebugOut(L"[INFO]Load map failed. \n");
}

void CMap::Render()
{
	D3DXVECTOR2 cam=CGame::GetInstance()->GetCurrentScene()->GetCamera()->position;

	for (int i = 0; i < layers.size(); i++)
	{
		//DebugOut(L"[INFO] Layer ID: %d \n",i);
		if (layers[i]->isVisible() == 1)
			layers[i]->Draw(cam.x, cam.y, tileset);
	}
	

}

int CMap::GetTileWidth()
{
	return tilewidth;
}

int CMap::GetTileHeight()
{
	return tileheight;
}

int CMap::GetRows()
{
	return rows;
}

int CMap::GetColumns()
{
	return columns;
}

D3DXVECTOR2 CMap::GetSize()
{
	return D3DXVECTOR2(tilewidth*columns,tileheight*rows);
}

CMap::~CMap()
{
}
