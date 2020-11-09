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
    D3DXVECTOR3 p(0, 0, 0);
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
            LPSPRITE tile = new CSprite(id, r,p, tex);
            tiles.push_back(tile);
            id++;
            
        }
    }

}
void Map::LoadMap()
{
    ifstream f;
    LPCWSTR path;
    f.open(mapfilePath);
    int tile_row, tile_column;
    f >> tile_row>>tile_column;
    f >> map_row >> map_column;
    for (int i = 0; i < map_row; i++)
    {
        for (int j = 0; j < map_column; j++)
        {
            f >> tile_map[i][j];
        }
    }
    f.close();
    AddTiles(WORLD_MAP_1_1, tile_row, tile_column, TILE_WIDTH, TILE_HEIGHT);
    DebugOut(L"[INFO]Load map successful. \n");
}
void Map::DrawMap(float c_x,float c_y)
{
    int begin_row = c_y / TILE_HEIGHT;
    int end_row = (c_y + SCREEN_HEIGHT) / TILE_HEIGHT + 1;
    int begin_column = c_x / TILE_WIDTH;
    int end_column = (c_x + SCREEN_WIDTH) / TILE_WIDTH + 1;

    /*DebugOut(L"b row %d\n", begin_row);
    DebugOut(L"e row %d\n", end_row);
    DebugOut(L"b c %d\n", begin_column);
    DebugOut(L"e c %d\n", end_column);*/
    for (int i = begin_row; i < end_row; i++)
    {
        for (int j = begin_column; j < end_column; j++)
        {
            int id = tile_map[i][j]-1;
            if (id != -1)
            {
                tiles[id]->Draw(j * TILE_WIDTH, i * TILE_HEIGHT);//hardcode không tốt , test
                //DebugOut(L"[INFO] ID: %d |X: %d | Y: %d \n",id, j * 48, i * 48.0);
            }
        }
    }
}