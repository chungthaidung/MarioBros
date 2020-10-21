#include "Map.h"
#include "debug.h"
#include "CTextures.h"
#include <iostream>
#include <fstream>
Map::Map(LPCWSTR filePath)
{
    mapfilePath = filePath;
}
void Map::AddTiles(int texID, int row, int column, int tile_width, int tile_height)
{
    RECT r;
    int id = 0;
    LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
    for (int i = 0; i < row; i++) //duyệt theo hàng từ trái -> phải từ trên -> dưới
    {
        for (int j = 0; j < column; j++)
        {
            r.left = j * tile_width;
            r.top = i * tile_height;
            r.right = j * tile_width + tile_width;
            r.bottom = i * tile_height + tile_height;
            LPSPRITE tile = new CSprite(id, r, tex);
            tiles.push_back(tile);
            id++;
            
        }
    }

}
void Map::LoadMap()
{
    ifstream f;
    int height;
    f.open(mapfilePath);
    f >> map_row >> map_column >> height;
    for (int i = 0; i < map_row; i++)
    {
        for (int j = 0; j < map_column; j++)
        {
            f >> tile_map[i][j];
        }
    }
    f.close();
    CTextures::GetInstance()->Add(WORLD_MAP_1_1, L"Resources/map/Final1(48).png", D3DCOLOR_XRGB(255, 255, 255)); // hardcode không tốt , test
    AddTiles(WORLD_MAP_1_1, 30, 29, 48, 48);//hardcode
    DebugOut(L"[INFO]Load map successful. \n");
}
void Map::DrawMap()
{
    for (int i = 0; i < map_row; i++)
    {
        for (int j = 0; j < map_column; j++)
        {
            int id = tile_map[i][j]-1;
            if (id != -1)
            {
                tiles[id]->Draw(j * 48.0, i * 48.0);//hardcode không tốt , test
                //DebugOut(L"[INFO] ID: %d |X: %d | Y: %d \n",id, j * 48, i * 48.0);
            }
        }
    }
}