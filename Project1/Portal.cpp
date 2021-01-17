#include "Portal.h"
#include "define.h"
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
