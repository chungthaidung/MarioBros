#include <algorithm>
#include "WorldScene.h"
#include "CPlaySceneKeyHandler.h"
#include "debug.h"
#include "CGame.h"
#include "CMap.h"
#include "Ground.h"
#include "WorldMario.h"
#include "Cactus.h"
#include "CheckPoint.h"
WorldScene::WorldScene(int id, std::string path):
	CScene(id,path)
{
	key_handler = new CPlayScenceKeyHandler(this);
	playtime = 0;
	player = NULL;
}

void WorldScene::LoadObjects()
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
				Camera* camera = new Camera(objgr);
				cam = camera;
			}
			else LoadObjGroup(objgr, objgr->Attribute("name"));
		}
		DebugOut(L"[INFO WORLD SCENE]Load Object successful. \n");
	}
}

void WorldScene::LoadObjGroup(TiXmlElement* data, std::string name)
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
			obj = new WorldMario();
			if (player != NULL)
			{
				DebugOut(L"[ERROR] WORLD MARIO object was created before!\n");
				continue;
			}
			//obj = new CMario(x, y);
			player = (WorldMario*)obj;
			if (CGame::GetInstance()->GetMario() != NULL)
			{
				player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());
			}
			DebugOut(L"[INFO] Player object created!\n");
		}
		else if (name.compare("Ground") == 0)
		{
			obj = new CGround();
		}
		else if(name.compare("Cactus")==0)
		{
			obj = new Cactus();
		}
		else if(name.compare("CheckPoint")==0)
		{
			obj = new CheckPoint(objdata);
		}
		
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
		if (obj->GetObjectType() == OBJECT_TYPE_WORLD_MARIO && CGame::GetInstance()->GetMarioWorldPos() != D3DXVECTOR2(0, 0))
		{
			obj->SetPosition(CGame::GetInstance()->GetMarioWorldPos().x, CGame::GetInstance()->GetMarioWorldPos().y);
		}
		//	DebugOut(L"[INFO]Object x: %d || y: %d || width: %f || height: %f. \n",x,y,width,height);
		objects.push_back(obj);
	}
}

void WorldScene::Load()
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
		hud->SetTarget(game->GetMario());
	}
	/*if (CGame::GetInstance()->GetMario() != NULL)
		player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());*/
	/*cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
	cam->SetTarget(player);*/
	DebugOut(L"[INFO] Done loading scene resources %s\n", ToLPCWSTR(scenePath));

}

void WorldScene::Update(DWORD dt)
{
	if (player == NULL) return;
	if (CGame::GetInstance()->GetMarioLife()>=0) {
		//DebugOut(L"[INFO WORLD] Mario level : %d\n", CGame::GetInstance()->GetMario()->GetLevel());

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
			objects[i]->Update(dt);
		}

		//	DebugOut(L"[EFFECT INFO2] Object SIZE: %d \n", objects.size());
		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->CollisionUpdate(dt, &coObjects);
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->FinalUpdate(dt);
		}
		for (size_t i = 0; i < effects.size(); i++)
		{
			effects[i]->Update(dt);
		}
		RemoveEffects();
		RemoveObjects();
		if(isUnload==true)
			CGame::GetInstance()->SwitchScene(switchsceneid);
	}
}

void WorldScene::Render()
{
	if (player == NULL) return;
	CGame::GetInstance()->SetViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
	std::sort(objects.begin(), objects.end(), CGameObject::rendercompare);
	gamemap->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	player->Render();
	CGame::GetInstance()->SetViewport(0, GAME_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	CGame::GetInstance()->GetDirect3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	hud->Render();
}

void WorldScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];
	objects.clear();
	effects.clear();
	//CGame::GetInstance()->SaveMarioState(CGame::GetInstance()->GetMario());
	//CGame::GetInstance()->SaveMarioState(player);
	player = NULL;
	DebugOut(L"[INFO WORLD MAP] Unload successful.\n");
	isUnload = false;
}

int WorldScene::GetSceneType()
{
	return WORLD_MAP;
}

WorldMario* WorldScene::GetPlayer()
{
	return player;
}
