#pragma once
#include "CGame.h"
#include "CTextures.h"
#include "CScene.h"
#include "CGameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Map.h"
#include "Camera.h"
//#include "Camera.h"
class CPlayScene : public CScene
{
protected:
	CMario* player;		// A play scene has to have player, right? 
	
	//Camera* cam;
	Map* map;
	D3DCOLOR mBackColor = 0x54acd2;;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);


public:
	CPlayScene(int id, LPCWSTR mapPath, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	
	CMario* GetPlayer() { return player; }
	//Camera* GetCamera() { return cam; }
	//friend class CPlayScenceKeyHandler;
};