#pragma once
#include "CGameObject.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
class Teleport :
    public CGameObject
{
public:
	Teleport(TiXmlElement* data);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int GetObjectType();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);
	RECT GetReBoundary();
	D3DXVECTOR2 GetRePosition();
	bool GetReMovingCam();
protected:
	RECT re_boundary;
	D3DXVECTOR2 re_position;
	bool re_movingcam;
};

