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
#include "Coin.h"
#include "QuestionBox.h"
#include "Brick.h"
#include "Piranha.h"
using namespace std;

CPlayScene::CPlayScene(int id,std::string Path) :
	CScene(id, Path)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

void CPlayScene::LoadObjects()
{
	TiXmlDocument doc(scenePath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* objgr = root->FirstChildElement("objectgroup"); objgr != NULL; objgr = objgr->NextSiblingElement("objectgroup"))
		{
			LoadObjGroup(objgr,objgr->Attribute("name"));
		}
		DebugOut(L"[INFO]Load Object successful. \n");

	}
}

void CPlayScene::LoadObjGroup(TiXmlElement* data,std::string name)
{
	CGameObject* obj = NULL;
	
	for (TiXmlElement* objdata = data->FirstChildElement("object"); objdata != NULL; objdata = objdata->NextSiblingElement("object"))
	{
		int visible = 1;
		objdata->QueryIntAttribute("visible", &visible);
		if (visible == 0) continue;
		int x, y;
		float width, height;
		objdata->QueryIntAttribute("x", &x);
		objdata->QueryIntAttribute("y", &y);
		if (name.compare("Mario") == 0) {
			obj = new CMario();
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				continue;
			}
			obj = new CMario(x, y);
			player = (CMario*)obj;
			DebugOut(L"[INFO] Player object created!\n");
		}
		else if (name.compare("Ground")==0)
		{
			obj = new CGround();
		}
		else if (name.compare("Ghost")==0) {
			obj = new GhostObject();
		}
		else if (name.compare("Enemies") == 0) {
			string enemy = objdata->Attribute("name");
			if (enemy.compare("Goomba") == 0)
			{
				int type, state;
				objdata->QueryIntAttribute("type", &type);
				obj = new Goomba(type);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &state);
				obj->SetState(state);
			}
			else if (enemy.compare("Koopa") == 0)
			{
				int type,state;
				objdata->QueryIntAttribute("type", &type);
				obj = new Koopa(type);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &state);
				obj->SetState(state);
			}
			else if (enemy.compare("Piranha") == 0)
			{
				int type;
				objdata->QueryIntAttribute("type", &type);
				obj = new Piranha(type,y);
			}
		}
		else if (name.compare("Misc") == 0)
		{
			string misc = objdata->Attribute("name");
			if (misc.compare("Coin") == 0)
			{
				obj = new Coin();
			}
			else if (misc.compare("QuestionBox") == 0)
			{
				int r;
				CGameObject* reward = NULL;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value",&r);
				switch (r)
				{
				case OBJECT_TYPE_COIN:
					reward = new Coin();
					break;
				}
				obj = new QuestionBox(reward,y);
			}
			else if (misc.compare("Brick") == 0)
			{
				int r,type;
				objdata->QueryIntAttribute("type", &type);
				CGameObject* reward = NULL;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &r);
				switch (r)
				{
				case OBJECT_TYPE_COIN:
					reward = new Coin();
					break;
				}
				obj = new Brick(reward,type, y);
			}
		}
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
	//	DebugOut(L"[INFO]Object x: %d || y: %d || width: %f || height: %f. \n",x,y,width,height);
		objects.push_back(obj);
		
	}
	
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", scenePath);
	LoadObjects();
	gamemap = new CMap(scenePath);//hardcode
	gamemap->LoadGameMap();
	CGame* game = CGame::GetInstance();
//	cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
//	cam->SetTarget(player);
	DebugOut(L"[INFO] Done loading scene resources %s\n", scenePath);
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
	

	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0; 
	if (cx  > gamemap->GetSize().x - game->GetScreenWidth()) cx = gamemap->GetSize().x - game->GetScreenWidth();
	CGame::GetInstance()->SetCamPos(cx, cy/*cy*/);//
	
	RemoveObjects();
}

void CPlayScene::Render()
{
	float x, y;
	CGame::GetInstance()->GetCamPos(x,y );
	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->GetObjectType()== OBJECT_TYPE_PIRANHA)
			objects[i]->Render();
	}
	gamemap->Render();
	for (int i = 1; i < objects.size(); i++)
	{
		if(objects[i]->GetObjectType()!=OBJECT_TYPE_PIRANHA)
			objects[i]->Render();
	}
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


