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
	CGameObject* target;
	//float y_ground;
	bool lock_cam=false;
	bool moving_cam = false;
	float vx;
public:
	Camera(TiXmlElement* data);
	void SetTarget(CGameObject* player);
	void Update(DWORD dt);
	void SetLockCam(bool a);
	void CameraFollowTarget();
	void MovingCamera(DWORD dt);
	void FinalUpdate(DWORD dt);
	void SetMovingCam(bool a);
	D3DXVECTOR2 position;
	D3DXVECTOR2 size= D3DXVECTOR2(GAME_WIDTH, GAME_HEIGHT);


};

