#pragma once
#include "CGame.h"
#include "CTextures.h"
#include "CScene.h"
#include "CGameObject.h"
#include "Ground.h"
#include "Mario.h"
#include "Grid.h"
class CPlayScene : public CScene
{
protected:
	CMario* player;		// A play scene has to have player, right? 
	//D3DCOLOR mBackColor = D3DCOLOR_XRGB(156, 252, 240);
	long delaytime = 0;
	Grid* grid;
	vector<LPGAMEOBJECT> listObjects;
public:
	CPlayScene(int id,std::string path,long ptime);
	void LoadObjects();
	void LoadGridData();
	void LoadObjGroup(TiXmlElement* data,std::string name);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual int GetSceneType();
	void SetDelayTime(DWORD delay);
	CMario* GetPlayer() { return player; }

	virtual void SpawnObject(CGameObject* obj, TiXmlElement* data);

//	Camera* GetCamera() { return cam; }
	//friend class CPlayScenceKeyHandler;
};