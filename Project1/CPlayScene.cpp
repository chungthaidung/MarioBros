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
#include "Teleport.h"
#include "Portal.h"
#include "MovingObject.h"
#include "UpMushroom.h"
#include "FloatingKoopa.h"
#include "rapidjson/document.h"

//using namespace std;
using namespace rapidjson;

CPlayScene::CPlayScene(int id,std::string Path,long ptime) :
	CScene(id, Path)
{
	key_handler = new CPlayScenceKeyHandler(this);
	timestart = ptime;
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
				//DebugOut(L"CREATE CAMERA  \n");
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
			if (CGame::GetInstance()->GetMario() != NULL) {
				player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());
				player->endgame_reward = CGame::GetInstance()->GetMario()->endgame_reward;
			}
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
				string type = objdata->Attribute("type");
				int typeint = GOOMBA, state;
				if (type.compare("Goomba") == 0)
					typeint = GOOMBA;
				else if (type.compare("RedGoomba") == 0)
					typeint = RED_GOOMBA;
				obj = new Goomba(typeint);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &state);
				obj->SetState(state);
			}
			else if (enemy.compare("Koopa") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_KOOPA, state;
				if (type.compare("Koopas") == 0)
					typeint = GREEN_KOOPA;
				else if (type.compare("RedKoopas") == 0)
					typeint = RED_KOOPA;
				obj = new Koopa(typeint);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &state);
				obj->SetState(state);
			}
			else if (enemy.compare("Piranha") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_TYPE, ny;
				if (type.compare("Venus") == 0)
					typeint = GREEN_TYPE;
				else if (type.compare("RedVenus") == 0)
					typeint = RED_TYPE;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &ny);
				obj = new Piranha(typeint,ny,y);
			}
			else if (enemy.compare("Venus") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_TYPE,ny;
				if (type.compare("Venus") == 0)
					typeint = GREEN_TYPE;
				else if (type.compare("RedVenus") == 0)
					typeint = RED_TYPE;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &ny);
				obj = new Venus(typeint,ny,y);
			}
			else if(enemy.compare("FloatingKoopa") == 0)
			{
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				string y_limit = property->Attribute("value");
				vector<string> b = ParseComa(y_limit);
				float t_limit = stof(b[0]);
				float b_limit = stof(b[1]);
				obj = new FloatingKoopa(t_limit,b_limit);
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
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value",&r);
				obj = new QuestionBox(r,y);
			}
			else if (misc.compare("Brick") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = BRICK_REWARD, r;
				if (type.compare("Brick") == 0)
					typeint = BRICK_BREAKABLE;
				else if (type.compare("QuestionBlock") == 0)
					typeint = BRICK_REWARD;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				property = property->FirstChildElement("property");
				property->QueryIntAttribute("value", &r);
				obj = new Brick(r, typeint, y);
			}
			else if (misc.compare("EndGameReward") == 0)
			{
				obj = new EndGameReward();
			}
			else if (misc.compare("MovingObject") == 0)
			{
				obj = new MovingObject();
			}
		}
		else if (name.compare("Teleport") == 0)
		{
			obj = new Teleport(objdata);
		}
		else if (name.compare("Portal") == 0)
		{
			obj = new Portal(objdata);
		}
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
		//DebugOut(L"[INFO]Object x: %d || y: %d || width: %f || height: %f. \n",x,y,width,height);
		objects.push_back(obj);
	}
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", ToLPCWSTR(scenePath));
	LoadObjects();
	gamemap = new CMap(scenePath);
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
	playtime = timestart;
	DebugOut(L"[INFO] Done loading scene resources %s\n", ToLPCWSTR(scenePath));
}

void CPlayScene::Update(DWORD dt)
{
	if (player == NULL) return;
	if(delaytime<=0 ){
		//DebugOut(L"[INFO MARIO LEVEL] Mario level : %d\n", CGame::GetInstance()->GetMario()->GetLevel());

		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}
		//DebugOut(L"[EFFECT INFO1] Object SIZE: %d \n", objects.size());
		float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
		float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
		cam->Update(dt);
		hud->Update(dt);
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
		cam->FinalUpdate(dt);
		for (size_t i = 0; i < objects.size(); i++)
		{
			if ((objects[i]->GetPosition().x< cx - CGame::GetInstance()->GetScreenWidth() * 1 / 2 || objects[i]->GetPosition().x > cx + CGame::GetInstance()->GetScreenWidth() * 3 / 2
				|| objects[i]->GetPosition().y < cy - CGame::GetInstance()->GetScreenHeight() * 1 / 2 || objects[i]->GetPosition().y > cy + CGame::GetInstance()->GetScreenHeight() * 3 / 2)
				&& objects[i]->GetObjectType() != OBJECT_TYPE_MARIO && objects[i]->GetObjectType() != OBJECT_TYPE_TAIL)
				continue;
			objects[i]->FinalUpdate(dt);
		}
		for (size_t i = 0; i < effects.size(); i++)
		{
			effects[i]->Update(dt);
		}
		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		RemoveEffects();
		RemoveObjects();
		playtime-=dt;
		if (playtime < 0)
		{
			player->SetState(MARIO_STATE_DIE);
			isUnload = true;
		}
		if (isUnload == true)
			CGame::GetInstance()->SwitchScene(switchsceneid);
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
	if(player->GetState()!=MARIO_STATE_DIE)
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
	//CMario* temp = player;
	CGame::GetInstance()->SaveMarioState(player);
	//DebugOut(L"[INFO UNLOAD PLAYSCENE] Mario level : %d\n", CGame::GetInstance()->GetMario()->GetLevel());
	player = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n",ToLPCWSTR(scenePath));
	isUnload = false;

}

int CPlayScene::GetSceneType()
{
	return PLAY_SCENE;
}

void CPlayScene::SetDelayTime(DWORD delay)
{
	delaytime = delay;
}

void CPlayScene::SpawnObject(CGameObject* obj, TiXmlElement* data)
{
	CScene::SpawnObject(obj, data);
	TiXmlElement* properties = data->FirstChildElement("properties");
	for (TiXmlElement* property = properties->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
	{
		string name = property->Attribute("name");
		if (name.compare("Grid") == 0)
		{ 
			Document document;
			document.Parse(property->Attribute("value"));
			for (auto& v : document.GetArray())
			{
				auto cr = v.GetObjectW();
				int x = cr["x"].GetInt();
				int y = cr["y"].GetInt();
				
				//grid->
			}
			document.Clear();
			break;
		}
	}
}


