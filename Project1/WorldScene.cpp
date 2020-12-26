#include "WorldScene.h"
#include "CPlaySceneKeyHandler.h"
#include "debug.h"
#include "CGame.h"
#include "CMap.h"
#include "Ground.h"
#include "WorldMario.h"
WorldScene::WorldScene(int id, std::string path):
	CScene(id,path)
{
	key_handler = new CPlayScenceKeyHandler(this);
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
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				continue;
			}
			//obj = new CMario(x, y);
			player = (WorldMario*)obj;
			if (CGame::GetInstance()->GetMario() != NULL)
				player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());
			DebugOut(L"[INFO] Player object created!\n");
		}
		else if (name.compare("Ground") == 0)
		{
			obj = new CGround();
		}
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
		//	DebugOut(L"[INFO]Object x: %d || y: %d || width: %f || height: %f. \n",x,y,width,height);
		objects.push_back(obj);
	}
}

void WorldScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", scenePath);
	LoadObjects();
	gamemap = new CMap(scenePath);
	hud = new HUD();
	gamemap->LoadGameMap();
	CGame* game = CGame::GetInstance();
	/*if (player != NULL && cam != NULL)
	{
		cam->SetTarget(player);
	}
	if (player != NULL)
	{
		hud->SetTarget(player);
	}*/
	//	cam = new Camera(game->GetScreenWidth() / 2, game->GetScreenHeight() / 2);
	//	cam->SetTarget(player);
	DebugOut(L"[INFO] Done loading scene resources %s\n", ToLPCWSTR(scenePath));

}

void WorldScene::Update(DWORD dt)
{
}

void WorldScene::Render()
{
}

void WorldScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];

	objects.clear();
	effects.clear();
	//CGame::GetInstance()->SaveMarioState(player);
	player = NULL;
}
