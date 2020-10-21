#include "Camera.h"



Camera::Camera(int width, int height)
{
	c_width = width;
	c_height = height;
}
void Camera::SetTarget(CMario* player)
{
	if (player != NULL)
		target = player;
}
void Camera::Update()
{
	if (target != NULL)
	{
		float cx, cy;
		target->GetPosition(cx, cy);
		p_x -= c_width;
		p_y -= c_height;
	}
}
void Camera::GetCamPosition(float& x, float& y)
{
	x = p_x;
	y = p_y;
}
void Camera::InWorld()
{
	if (p_x < 0)
		p_x = 0;
}