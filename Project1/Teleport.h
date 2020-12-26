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

	RECT GetReBoundary();
	D3DXVECTOR2 GetRePosition();
protected:
	RECT re_boundary;
	D3DXVECTOR2 re_position;
};

