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
		if (name.compare("boundary") == 0)
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
		else if (name.compare("moving_cam") == 0)
		{
			property->QueryBoolAttribute("value", &moving_cam);
			if (moving_cam) vx = 0.1;
		}
	}

}

void Camera::SetTarget(CGameObject* player)
{
	if (player != NULL) {
		target = player;
		//DebugOut(L"SET TARGET SUCCESFUL\n");
	}
}

void Camera::Update(DWORD dt)
{
	CameraFollowTarget();
	MovingCamera(dt);
}

void Camera::SetLockCam(bool a)
{
	lock_cam = a;
}

void Camera::CameraFollowTarget()
{
	if (moving_cam) return;
	if (target != NULL)
	{
		RECT boundary = CGame::GetInstance()->GetCurrentScene()->GetBoundary();
		//	DebugOut(L"[BOUNDARY] left: %d || top: %d || right: %d || bottom: %d \n", boundary.left, boundary.top, boundary.right, boundary.bottom);
			//D3DXVECTOR2 mapsize = CGame::GetInstance()->GetCurrentScene()->GetMap()->GetSize();
		position.x = target->GetPosition().x - size.x / 2;
		//position.y = y_ground;
		//DebugOut(L"cam x: %f || cam y: %f \n", position.x, y_ground);
		float l, t, r, b;
		target->GetBoundingBox(l, t, r, b);
		if (lock_cam == true && target->GetPosition().y - position.y < size.y / 4)
		{
			position.y = target->GetPosition().y - size.y / 4;
		}
		else if (b - position.y >= size.y - size.y / 3)
		{
			position.y = b - size.y + size.y / 3;
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
		if (target->GetObjectType() != OBJECT_TYPE_MARIO) {
			position.x = 0;
			position.y = 0;
		}
			
		//DebugOut(L"[INFO BOUNDARY] y: %f \n", boundary.bottom - size.y);
	}
}

void Camera::MovingCamera(DWORD dt)
{
	if (!moving_cam) return;
	if (target != NULL)
	{
		RECT boundary = CGame::GetInstance()->GetCurrentScene()->GetBoundary();
		//position.x = target->GetPosition().x - size.x / 2;
		float l, t, r, b;
		target->GetBoundingBox(l, t, r, b);
		position.y = b - size.y + size.y / 3;;
		if (l < position.x)
		{
			target->SetPosition(position.x, t);
		}
		else if (r > position.x + size.x)
		{
			target->SetPosition(position.x + size.x-(r-l), t);
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
		}
	}
}

void Camera::FinalUpdate(DWORD dt)
{
	if (!moving_cam) return;
	if (target != NULL)
	{
		position.x += vx * dt;
	}
}

void Camera::SetMovingCam(bool a)
{
	moving_cam = a;
}

bool Camera::IsMovingCam()
{
	return moving_cam;
}
