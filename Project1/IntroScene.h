#pragma once
#include "CScene.h"
class IntroScene :
    public CScene
{
protected:
	CGameObject* target;
public:
	IntroScene(int id, std::string path);
	void LoadObjects();
	void LoadObjGroup(TiXmlElement* data, std::string name);
	virtual void Load();
	virtual void Unload();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual int GetSceneType();
};

