#pragma once
#include "CKeyEventHandler.h"
#include <d3dx9.h>
#include <d3d9.h>
#include <string>
#include "CGameObject.h"
#include "Effect.h"
class CScene
{
protected:
	CKeyEventHandler* key_handler;
	int id;
	std::string scenePath;

	vector<LPGAMEOBJECT> objects;
	vector<LPEFFECT> effects;


public:
	CScene(int id, std::string path);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void RemoveObjects();
	virtual void SpawnObject(CGameObject* obj);
	virtual void DespawnObject(CGameObject* obj);	
	virtual void RemoveEffects();
	virtual void AddEffect(LPEFFECT ef);
	virtual void DeleteEffect(LPEFFECT ef);
};
typedef CScene* LPSCENE;
