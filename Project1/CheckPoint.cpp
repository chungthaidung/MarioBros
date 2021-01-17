#include "CheckPoint.h"
#include "Utils.h"
CheckPoint::CheckPoint(TiXmlElement* data)
{
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("sceneID") == 0)
		{
			property->QueryIntAttribute("value", &sceneID);
		}
		else if (name.compare("position") == 0)
		{
		}
		else if (name.compare("cantele") == 0)
		{
			property->QueryBoolAttribute("value", &canTele);
		}
		else if (name.compare("collision") == 0)
		{
			string collision = property->Attribute("value");
			vector<string> b = ParseComa(collision);
			float x = stof(b[0]);
			float y = stof(b[1]);
			ncollision.x = x;
			ncollision.y = y;
		}
		
	}
}

void CheckPoint::Render()
{
	RenderBoundingBox();
}

void CheckPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x+width;
	bottom = y+height;
}

int CheckPoint::GetObjectType()
{
	return OBJECT_TYPE_CHECKPOINT;
}

int CheckPoint::GetSceneID()
{
	return sceneID;
}

bool CheckPoint::CanTele()
{
	return canTele;
}

D3DXVECTOR2 CheckPoint::GetNCollision()
{
	return ncollision;
}
