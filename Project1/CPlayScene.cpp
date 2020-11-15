#include <iostream>
#include <fstream>

#include "define.h"
#include "debug.h"
#include "CPlayScene.h"
#include "Utils.h"
#include "CTextures.h"
#include "CSprites.h"
#include "CScenceKeyHandler.h"
#include "CAnimations.h"
#include "CPlaySceneKeyHandler.h"
#include "CAnimationSets.h"
#include "GhostObject.h"
#include "Goomba.h"
#include "Koopa.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR mapPath, LPCWSTR filePath) :
	CScene(id,mapPath, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());
	int w = atoi(tokens[4].c_str());
	int h = atoi(tokens[5].c_str());
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;
	
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_GOOMBA: obj = new Goomba(); break;
	case OBJECT_TYPE_GHOST: obj = new GhostObject(); break;
	case OBJECT_TYPE_KOOPA: obj = new Koopa(); break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	obj->SetWidthHeight(w, h);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	map = new Map(mapFilePath);
	map->LoadMap();
	CGame* game = CGame::GetInstance();
//	cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
//	cam->SetTarget(player);
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	
	
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->CollisionUpdate(dt, &coObjects);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->FinalUpdate(dt);
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
//	cam->GetCamPosition(cx, cy);
	player->GetPosition(cx, cy);
	CGame* game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	//cy = CAMERA_Y_POSITION * 2 / 3;
	if (cy > game->GetScreenHeight() + 48)
		cy = CAMERA_Y_POSITION;
	else if (cy < 768)
	{
		cy -= 48;
	}
	
	//cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
	//cam->SetCamPosition(cx, cy); //dùng để set cam nhưng chưa tạo được class cam
	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0; 
	//if (cx + game->GetScreenWidth() > map->GetColumn() * 48) cx = map->GetColumn() * 48 - game->GetScreenWidth(); //hardcode
	CGame::GetInstance()->SetCamPos(cx, cy/*cy*/);//
	
	RemoveObjects();
}
void CPlayScene::Render()
{
	float x, y;
	CGame::GetInstance()->GetCamPos(x,y );
	map->DrawMap(x,y);
	for (int i = 1; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	//DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


