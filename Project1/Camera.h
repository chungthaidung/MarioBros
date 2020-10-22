#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Mario.h"
class Camera 
{//Camera tự update theo object => bỏ *obj zo cam
protected:
	int c_width, c_height;
	float p_x = 0.0f, p_y = 0.0f;
	CMario* target;
	
public:
	Camera(int width, int height);
	void InWorld();
	void SetTarget(CMario* player);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetCamPosition(float &x,float &y);
	


};

