#pragma once
#include "CGame.h"
#include "CTextures.h"
#include "CScene.h"
#include "CGameObject.h"
#include "Ground.h"
#include "Mario.h"
#include "Map.h"
#include "CMap.h"

class CPlayScene : public CScene
{
protected:
	CMario* player;		// A play scene has to have player, right? 
	
//	Camera* cam;
	//D3DCOLOR mBackColor = D3DCOLOR_XRGB(156, 252, 240);
	CMap* gamemap;


public:
	CPlayScene(int id,std::string path);
	void LoadObjects();
	void LoadObjGroup(TiXmlElement* data,std::string name);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }
//	Camera* GetCamera() { return cam; }
	//friend class CPlayScenceKeyHandler;
};