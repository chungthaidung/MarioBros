#include "CGameMap.h"

CGameMap::CGameMap(string filePath)
{
    LoadMap(filePath);
}

CGameMap::~CGameMap()
{
    delete mMap;
}

void CGameMap::LoadMap(string filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset* tileset = mMap->GetTileset(i);
        string toImage = tileset->GetImage()->GetSource().c_str();

        CTextures::GetInstance()->Add(WORLD_MAP_1_1, ToLPCWSTR(toImage), D3DCOLOR_XRGB(255, 128, 192));
        LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(WORLD_MAP_1_1);
        // LPSPRITE sprite = new CSprite(WORLD_MAP_1_1, RECT(), tex);

        ListTileset.insert(pair<int, LPDIRECT3DTEXTURE9>(i, tex));
    }
    DebugOut(L"Load map success!");
}

Tmx::Map* CGameMap::GetMap()
{
    return mMap;
}

int CGameMap::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int CGameMap::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int CGameMap::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int CGameMap::GetTileHeight()
{
    return mMap->GetTileHeight();
}

void CGameMap::Draw()
{
    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        RECT sourceRECT;



        for (size_t m = 0; m < layer->GetHeight(); m++)
        {
            for (size_t n = 0; n < layer->GetWidth(); n++)
            {
                int tilesetIndex = layer->GetTileTilesetIndex(n, m);

                if (tilesetIndex != -1)
                {
                    const Tmx::Tileset* tileSet = mMap->GetTileset(tilesetIndex);

                    int tileWidth = mMap->GetTileWidth();
                    int tileHeight = mMap->GetTileHeight();

                    int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                    int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

                    LPDIRECT3DTEXTURE9 texture = ListTileset[layer->GetTileTilesetIndex(n, m)];

                    //tile index
                    int tileID = layer->GetTileId(n, m);

                    int y = tileID / tileSetWidth;
                    int x = tileID - y * tileSetWidth;

                    sourceRECT.top = y * tileHeight;
                    sourceRECT.bottom = sourceRECT.top + tileHeight;
                    sourceRECT.left = x * tileWidth;
                    sourceRECT.right = sourceRECT.left + tileWidth;
                    LPSPRITE sprite = new CSprite(tileID, sourceRECT, texture);
                    //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                    //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                 //   D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);
                    int position_x = n * tileWidth + tileWidth / 2;
                    int position_y = m * tileHeight + tileHeight / 2;
                    sprite->Draw(position_x, position_y);

                }
            }
        }

    }
}