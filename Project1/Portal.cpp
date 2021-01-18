#include "Portal.h"
#include "define.h"
#include "CGame.h"
#include "Utils.h"
Portal::Portal(TiXmlElement* data)
{
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("sceneID") == 0)
		{
			property->QueryIntAttribute("value", &sceneID);
		}
		else if (name.compare("world_pos") == 0)
		{
			string world_pos = property->Attribute("value");
			vector<string> b = ParseComa(world_pos);
			float x = stof(b[0]);
			float y = stof(b[1]);
			D3DXVECTOR2 pos = D3DXVECTOR2(x, y);
			CGame::GetInstance()->SaveMarioWorldPos(pos);
		}
	}
}

void Portal::Render()
{
	RenderBoundingBox();
}

void Portal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

int Portal::GetObjectType()
{
	return OBJECT_TYPE_PORTAL;
}

int Portal::GetSceneID()
{
	return sceneID;
}

bool Portal::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
		return false;
	return true;
}
