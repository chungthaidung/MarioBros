#include "Camera.h"
#include "debug.h"
#include "CGame.h"
#include "CMap.h"
#include "Utils.h"

Camera::Camera(TiXmlElement* data)
{
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("y_ground") == 0)
		{
			property->QueryFloatAttribute("value", &y_ground);
			//DebugOut(L"y ground: %f \n", y_ground);

		}
		else if (name.compare("boundary") == 0)
		{
			string boundary = property->Attribute("value");
			vector<string> boun = ParseComa(boundary);
			long left = stoi(boun[0]);
			long top = stoi(boun[1]);
			long right = stoi(boun[2]);
			long bottom = stoi(boun[3]);
			RECT a{ left,top,right,bottom };
			//DebugOut(L"[BOUNDARY] left: %d || top: %d || right: %d || bottom: %d \n", left, top, right, bottom);
			CGame::GetInstance()->GetCurrentScene()->SetBoundary(a);
		
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
		RECT boundary = CGame::GetInstance()->GetCurrentScene()->GetBoundary();
	//	DebugOut(L"[BOUNDARY] left: %d || top: %d || right: %d || bottom: %d \n", boundary.left, boundary.top, boundary.right, boundary.bottom);
		//D3DXVECTOR2 mapsize = CGame::GetInstance()->GetCurrentScene()->GetMap()->GetSize();
		position.x = target->GetPosition().x - size.x/2;
		//position.y = y_ground;
		//DebugOut(L"cam x: %f || cam y: %f \n", position.x, y_ground);

		if (lock_cam==true && target->GetPosition().y - position.y < size.y / 4)
		{
			position.y = target->GetPosition().y - size.y / 4;
		}
		else if ( target->GetBoundingBox().bottom -position.y >= size.y-96)
		{
			position.y = target->GetBoundingBox().bottom-size.y +96;
		//	DebugOut(L"[INFO CAMERA]x: %f || y: %f \n", position.x, position.y);
		}
		if (position.x < boundary.left)
			position.x = boundary.left;
		if (position.x > boundary.right - size.x) 
			position.x = boundary.right - size.x;

		if (position.y < boundary.top)
			position.y = boundary.top;
		if (position.y > boundary.bottom - size.y)
		{
			position.y = boundary.bottom - size.y;
			lock_cam = false;
		}
		//DebugOut(L"[INFO BOUNDARY] y: %f \n", boundary.bottom - size.y);

		//else if()
	}
}

void Camera::SetLockCam(bool a)
{
	lock_cam = a;
}
