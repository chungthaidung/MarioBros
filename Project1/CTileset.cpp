#include "CTileset.h"
#include "define.h"
#include "debug.h"
CTileset::CTileset(TiXmlElement* data)
{
    int tilecount=0;
    data->QueryIntAttribute("firstgid", &firstgid);
    data->QueryIntAttribute("tilewidth", &tilewidth);
    data->QueryIntAttribute("tileheight", &tileheight);
    data->QueryIntAttribute("columns", &columns);
    data->QueryIntAttribute("tilecount", &tilecount);
    rows = tilecount / columns;
    int sceneid = CGame::GetInstance()->GetCurrentSceneID();
    switch (sceneid)
    {
    case 1:
    case 2:
        texture = CTextures::GetInstance()->Get(WORLD_1_1);
        DebugOut(L"[INFO] WORLD_1_1 \n");
        break;
    case 0:
        texture = CTextures::GetInstance()->Get(WORLD_MAP_1);
        DebugOut(L"[INFO] WORLD_MAP_1 \n");
        break;
    }
    AddTiles();
}

void CTileset::AddTiles()
{
    RECT r;
    D3DXVECTOR3 p(0, 0, 0);
    int id = 0;
    for (int i = 0; i < rows; i++) //duyệt theo hàng từ trái -> phải từ trên -> dưới
    {
        for (int j = 0; j < columns; j++)
        {
            r.left = j * tilewidth;
            r.top = i * tileheight;
            r.right = j * tilewidth + tilewidth;
            r.bottom = i * tileheight + tileheight;
            LPSPRITE tile = new CSprite(id, r, p, texture);
            tiles.push_back(tile);
            id++;
        }
    }

}



void CTileset::Draw(int id, float x, float y)
{
    tiles[id]->Draw(x, y);

}

int CTileset::GetTileWidth()
{
    return tilewidth;
}

int CTileset::GetTileHeight()
{
    return tileheight;
}
