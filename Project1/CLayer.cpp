#include "CLayer.h"
#include "define.h"
#include "debug.h"
CLayer::CLayer(TiXmlElement* data)
{
    int tilecount;
    data->QueryIntAttribute("id", &id);
    data->QueryIntAttribute("height", &layer_rows);
    data->QueryIntAttribute("width", &layer_columns);
    TiXmlElement* mapdata = data->FirstChildElement("data");
    string map = mapdata->GetText();
    vector<string> tilemap= ParseComa(map);
    for (int i = 0; i < layer_rows; i++)
    {
        for (int j = 0;j < layer_columns; j++)
        {
            tile[i][j] = stoi(tilemap[i + j]);
        }
    }
  //  DebugOut(L"[INFO]Layer ID: %d \n",id);

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
            int id = tile[i][j] - 1;
            if (id != -1)
            {
                tileset->Draw(id, j * tilewidth, i * tileheight);//hardcode không tốt , test
              //  DebugOut(L"[INFO] ID: %d |X: %d | Y: %d \n",id, j * 48, i * 48.0);
            }
        }
    }
}

CLayer::~CLayer()
{
}
