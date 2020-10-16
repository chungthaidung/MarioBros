#pragma once
class Camera
{
protected:
	int c_width, c_height;
	float c_x, c_y;
public:
	Camera(int width, int height);
	void SetCamPosition(float x, float y);
	int GetWidth();
	int GetHeight();
	void GetCamPos(float &x,float &y);



};

