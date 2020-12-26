#include "Teleport.h"
#include "Utils.h"
#include "debug.h"
Teleport::Teleport(TiXmlElement* data)
{
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("boundary") == 0)
		{
			string boundary = property->Attribute("value");
			vector<string> b = ParseComa(boundary);
			re_boundary = RECT{ stoi(b[0]),stoi(b[1]),stoi(b[2]),stoi(b[3]) };
		}
		else if (name.compare("tele_position") == 0)
		{
			string reposition = property->Attribute("value");
			vector<string> b = ParseComa(reposition);
			float x = stof(b[0]);
			float y = stof(b[1]);
			re_position.x =x;
			re_position.y =y;
			//DebugOut(L"RePosition mario: x: %f || y: %f \n", x, y);

			//DebugOut(L"RePosition mario: %s \n", ToLPCWSTR(reposition));

		}
	}
	//DebugOut(L"ReBoundary: left: %d || top: %d || right: %d || bottom: %d\n", re_boundary.left, re_boundary.top, re_boundary.right, re_boundary.bottom);

}
void Teleport::Render()
{
	RenderBoundingBox();
}

void Teleport::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

int Teleport::GetObjectType()
{
	return OBJECT_TYPE_TELEPORT;
}

RECT Teleport::GetReBoundary()
{
	return re_boundary;
}

D3DXVECTOR2 Teleport::GetRePosition()
{
	return re_position;
}

