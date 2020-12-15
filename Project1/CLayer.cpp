#include "CLayer.h"
#include "define.h"
#include "debug.h"
CLayer::CLayer(TiXmlElement* data)
{
    int tilecount;
    visible = 1;
    data->QueryIntAttribute("id", &id);
    data->QueryIntAttribute("height", &layer_rows);
    data->QueryIntAttribute("width", &layer_columns);
    data->QueryIntAttribute("visible", &visible);
    TiXmlElement* mapdata = data->FirstChildElement("data");
    string map = mapdata->GetText();
    vector<string> tilemap= ParseComa(map);
    int n = 0;
    for (int i = 0; i < layer_rows && n < tilemap.size(); i++)
    {
        for (int j = 0;j < layer_columns; j++,n++)
        {
            tile[i][j] = stoi(tilemap[n]);
        }
    }
  //  DebugOut(L"[INFO]Layer ID: %d \n",id);

}

void CLayer::SetVisible(int set)
{
    visible = set;
}

int CLayer::isVisible()
{
    return visible;
}

void CLayer::Draw(float cam_x, float cam_y, CTileset* tileset)
{
    int tileheight = tileset->GetTileHeight();
    int tilewidth = tileset->GetTileWidth();
    int begin_row = cam_y / tileheight;
    int end_row = (cam_y + SCREEN_HEIGHT) / tileheight + 1;
    int begin_column = cam_x / tilewidth;
    int end_column = (cam_x + SCREEN_WIDTH) / tilewidth + 1;

    /*DebugOut(L"b row %d\n", begin_row);
    DebugOut(L"e row %d\n", end_row);
    DebugOut(L"b c %d\n", begin_column);
    DebugOut(L"e c %d\n", end_column);*/
    for (int i = begin_row; i < end_row; i++)
    {
        for (int j = begin_column; j < end_column; j++)
        {
            int idtile = tile[i][j] - 1;
            if (idtile != -1)
            {
                tileset->Draw(idtile, j * tilewidth, i * tileheight);//hardcode không tốt , test
             //   DebugOut(L"[INFO] Layer ID: %d | ID: %d |X: %d | Y: %d \n", id ,idtile, j * 48, i * 48.0);
            }
        }
    }
}

CLayer::~CLayer()
{
}
