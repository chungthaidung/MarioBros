#pragma once
#include "CGame.h"
#include "CTextures.h"
#include "CScene.h"
#include "CGameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "CGameMap.h"
//#include "Camera.h"
class CPlayScene : public CScene
{
protected:
	CMario* player;		// A play scene has to have player, right? 
	
	CGameMap* mMap;

	D3DCOLOR mBackColor = 0x4866ff;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CPlayScene(int id, std::string mapPath, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	string GetMapPath() { return sceneMapPath; }
	CMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};