#pragma once


#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "debug.h"
#include "CSprite.h"
#include "MapReader/Tmx.h.in"
#include "define.h"
#include "CTextures.h"
#include "Utils.h"



class CGameMap
{
public:
    CGameMap(string filePath);

    Tmx::Map* GetMap();

    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();

    void Draw();

    ~CGameMap();

private:
    void LoadMap(string filePath);

    Tmx::Map* mMap;
    map<int, LPDIRECT3DTEXTURE9>          ListTileset;
};



