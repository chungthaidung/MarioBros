#pragma once
#include "CScene.h"
#include "WorldMario.h"
class WorldScene :
    public CScene
{
protected:
    WorldMario* player;
public:
    WorldScene(int id, std::string path);
	void LoadObjects();
	void LoadObjGroup(TiXmlElement* data, std::string name);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

