#include "Camera.h"



Camera::Camera(int width, int height)
{
	c_width = width;
	c_height = height;
}
void Camera::SetCamPosition(float x, float y) {
	c_x = x;
	c_y = y;
}
int Camera::GetWidth()
{
	return c_width;
}
int Camera::GetHeight()
{
	return c_height;
}
void Camera::GetCamPos(float &x,float &y)
{
	x = c_x;
	y = c_y;
}