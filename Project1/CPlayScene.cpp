#include <iostream>
#include <fstream>
#include <algorithm>

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
#include "EndGameReward.h"
#include "Venus.h"
#include "CMap.h"
using namespace std;

CPlayScene::CPlayScene(int id,std::string Path,long ptime) :
	CScene(id, Path)
{
	key_handler = new CPlayScenceKeyHandler(this);
	playtime = ptime;
}

void CPlayScene::LoadObjects()
{
	TiXmlDocument doc(scenePath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* objgr = root->FirstChildElement("objectgroup"); objgr != NULL; objgr = objgr->NextSiblingElement("objectgroup"))
		{
			string name = objgr->Attribute("name");
			if (name.compare("Camera") == 0)
			{
				DebugOut(L"CREATE CAMERA  \n");
				Camera* camera = new Camera(objgr);
				cam = camera;
			}
			else LoadObjGroup(objgr,objgr->Attribute("name"));
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
			if(CGame::GetInstance()->GetMario()!=NULL)
				player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());
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
				int type,ny;
				objdata->QueryIntAttribute("type", &type);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &ny);
				obj = new Piranha(type,ny,y);
			}
			else if (enemy.compare("Venus") == 0)
			{
				int type,ny;
				objdata->QueryIntAttribute("type", &type);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &ny);
				obj = new Venus(type,ny,y);
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
				obj = new QuestionBox(r,y);
			}
			else if (misc.compare("Brick") == 0)
			{
				int r,type;
				objdata->QueryIntAttribute("type", &type);
				CGameObject* reward = NULL;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &r);
				
				obj = new Brick(r,type, y);
			}
			else if (misc.compare("EndGameReward") == 0)
			{
				obj = new EndGameReward();
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
	hud = new HUD();
	gamemap->LoadGameMap();
	CGame* game = CGame::GetInstance();
	if (player != NULL && cam != NULL)
	{
		cam->SetTarget(player);
	}
	if (player != NULL)
	{
		hud->SetTarget(player);
	}
//	cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
//	cam->SetTarget(player);
	DebugOut(L"[INFO] Done loading scene resources %s\n", scenePath);
}

void CPlayScene::Update(DWORD dt)
{
	if(delaytime<=0){
		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}
		//DebugOut(L"[EFFECT INFO1] Object SIZE: %d \n", objects.size());
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
		for (size_t i = 0; i < objects.size(); i++)
		{
			if ((objects[i]->GetPosition().x< cx - CGame::GetInstance()->GetScreenWidth() * 1 / 2 || objects[i]->GetPosition().x > cx + CGame::GetInstance()->GetScreenWidth() * 3 / 2
				|| objects[i]->GetPosition().y < cy - CGame::GetInstance()->GetScreenHeight() * 1 / 2 || objects[i]->GetPosition().y > cy + CGame::GetInstance()->GetScreenHeight() * 3 / 2)
				&& objects[i]->GetObjectType() != OBJECT_TYPE_MARIO && objects[i]->GetObjectType() != OBJECT_TYPE_TAIL)
				continue;
			objects[i]->Update(dt);
		}
		
		//	DebugOut(L"[EFFECT INFO2] Object SIZE: %d \n", objects.size());
		for (size_t i = 0; i < objects.size(); i++)
		{
			if ((objects[i]->GetPosition().x< cx - CGame::GetInstance()->GetScreenWidth() * 1 / 2 || objects[i]->GetPosition().x > cx + CGame::GetInstance()->GetScreenWidth() * 3 / 2
				|| objects[i]->GetPosition().y < cy - CGame::GetInstance()->GetScreenHeight() * 1 / 2 || objects[i]->GetPosition().y > cy + CGame::GetInstance()->GetScreenHeight() * 3 / 2)
				&& objects[i]->GetObjectType() != OBJECT_TYPE_MARIO && objects[i]->GetObjectType() != OBJECT_TYPE_TAIL)
				continue;
			objects[i]->CollisionUpdate(dt, &coObjects);
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			if ((objects[i]->GetPosition().x< cx - CGame::GetInstance()->GetScreenWidth() * 1 / 2 || objects[i]->GetPosition().x > cx + CGame::GetInstance()->GetScreenWidth() * 3 / 2
				|| objects[i]->GetPosition().y < cy - CGame::GetInstance()->GetScreenHeight() * 1 / 2 || objects[i]->GetPosition().y > cy + CGame::GetInstance()->GetScreenHeight() * 3 / 2)
				&& objects[i]->GetObjectType() != OBJECT_TYPE_MARIO && objects[i]->GetObjectType() != OBJECT_TYPE_TAIL)
				continue;
			objects[i]->FinalUpdate(dt);
		}
		hud->Update(dt);
		for (size_t i = 0; i < effects.size(); i++)
		{
			effects[i]->Update(dt);
		}
		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		if (player == NULL) return;
		cam->Update(dt);
		// Update camera to follow mario
		//float cx, cy;
		////	cam->GetCamPosition(cx, cy);
		//player->GetPosition(cx, cy);
		//CGame* game = CGame::GetInstance();
		//cx -= game->GetScreenWidth() / 2;
		////cy = CAMERA_Y_POSITION * 2 / 3;
		//if (cy > game->GetScreenHeight() + 48)
		//	cy = CAMERA_Y_POSITION;
		//else if (cy < 768)
		//{
		//	cy -= 48;
		//}
		//if (cx < 0) cx = 0;
		//if (cy < 0) cy = 0;
		//if (cx > gamemap->GetSize().x - game->GetScreenWidth()) cx = gamemap->GetSize().x - game->GetScreenWidth();
		//CGame::GetInstance()->SetCamPos(cx, cy/*cy*/);//
		//DebugOut(L"[INFO]Cam_x: %f || Cam_y: %f \n",cx,cy);
		RemoveEffects();
		RemoveObjects();
		playtime-=dt;
		
		//DebugOut(L"[INFO] Play time : %d\n", playtime);
	}
	else
	{
		delaytime -= dt;
		//DebugOut(L"[STOP]\n");
	}

}

void CPlayScene::Render()
{
	/*float x, y;
	x = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	y = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;*/
	//CGame::GetInstance()->GetCamPos(x, y);
	CGame::GetInstance()->SetViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);

	std::sort(objects.begin(), objects.end(), CGameObject::rendercompare);

	for (int i = 0; i < objects.size() && objects[i]->renderOrder < 2; i++)
	{
		if (objects[i]->GetObjectType() != OBJECT_TYPE_MARIO)
			objects[i]->Render();
	}
	gamemap->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->renderOrder >= 2)
			objects[i]->Render();

	}
	player->Render();
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}

	CGame::GetInstance()->SetViewport(0,GAME_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	CGame::GetInstance()->GetDirect3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
	hud->Render();
}
/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];

	objects.clear();
	effects.clear();
	CGame::GetInstance()->SaveMarioState(player);
	player = NULL;

	//DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

long CPlayScene::GetPlayTime()
{
	return playtime;
}

void CPlayScene::SetDelayTime(DWORD delay)
{
	delaytime = delay;
}


