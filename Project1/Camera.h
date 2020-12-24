#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
#include "Mario.h"
#include "define.h"
class Camera 
{//Camera tự update theo object => bỏ *obj zo cam
protected:
	CMario* target;
	float y_limit;
public:
	Camera(TiXmlElement* data);
	void SetTarget(CMario* player);
	void Update(DWORD dt);
	
	D3DXVECTOR2 position;
	D3DXVECTOR2 size= D3DXVECTOR2(GAME_WIDTH, GAME_HEIGHT);


};

