#include "Camera.h"
#include "debug.h"
#include "CGame.h"
#include "CMap.h"
Camera::Camera(TiXmlElement* data)
{
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("y_limit") == 0)
		{
			property->QueryFloatAttribute("value", &y_limit);
		}
	}

}

void Camera::SetTarget(CMario* player)
{
	if (player != NULL) {
		target = player;
		//DebugOut(L"SET TARGET SUCCESFUL\n");
	}
}

void Camera::Update(DWORD dt)
{
	if (target != NULL)
	{
		D3DXVECTOR2 mapsize = CGame::GetInstance()->GetCurrentScene()->GetMap()->GetSize();
		position.x = target->GetPosition().x - size.x/2;
		position.y = y_limit;
		//position.x = cx;
		if (position.x < 0)position.x = 0;
		if (position.y < 0)position.y = 0;
		else if (position.x > mapsize.x - size.x)position.x = mapsize.x - size.x;
	//	DebugOut(L"[INFO CAMERA]x: %f || y: %f \n",position.x,position.y);

		//else if()
	}
}
