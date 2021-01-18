#pragma once
#include "CGameObject.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
class Portal :
    public CGameObject
{
public:
	Portal(TiXmlElement* data);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int GetObjectType();
	int GetSceneID();
	virtual bool GetThrough(CGameObject* obj, D3DXVECTOR2 direction);

protected:
	int sceneID;

};

