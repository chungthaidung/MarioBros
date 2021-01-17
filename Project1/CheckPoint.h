#pragma once
#include "CGameObject.h"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"
class CheckPoint :
    public CGameObject
{
protected:
    int sceneID;
	bool canTele;
	D3DXVECTOR2 ncollision;
public:
    CheckPoint(TiXmlElement* data);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetObjectType();
	int GetSceneID();
	bool CanTele();
	D3DXVECTOR2 GetNCollision();
};

