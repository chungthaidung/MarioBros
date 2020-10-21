#pragma once
class Camera 
{//Camera tự update theo object => bỏ *obj zo cam
protected:
	int c_width, c_height;
	float p_x = 0.0f, p_y = 0.0f;
	
public:
	Camera(int width, int height);
	void SetCamPosition(float x, float y);
	int GetWidth();
	int GetHeight();
	void GetCamPos(float &x,float &y);
	void InWorld();


};

