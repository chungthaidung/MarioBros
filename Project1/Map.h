#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "debug.h"
#include "CSprite.h"
#include "define.h"
#include "Utils.h"

#define TILE_WIDTH  48
#define TILE_HEIGHT 48
class Map
{
private:
    int map_column, map_row;
    LPCWSTR mapfilePath;
    int tile_map[500][500];

    vector<LPSPRITE> tiles;
public:
    Map(LPCWSTR filePath);
    void AddTiles(int texID, int row, int column, int tile_width, int tile_height);
    void LoadMap();
    int GetColumn() { return map_column;}
    int GetRow() { return map_row; }
    void DrawMap(float c_x,float c_y);

    ~Map();

};

