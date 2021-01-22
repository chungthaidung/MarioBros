#include "IntroScene.h"
#include "CIntroSceneKeyHandler.h"
#include "debug.h"
#include "CGame.h"
#include "CMap.h"
#include "Opening.h"
IntroScene::IntroScene(int id, std::string path) :CScene(id, path)
{
	key_handler = new CIntroSceneKeyHandler(this);
}

void IntroScene::LoadObjects()
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
		DebugOut(L"[INFO]Load Object successful. \n");
	}
}

void IntroScene::LoadObjGroup(TiXmlElement* data, std::string name)
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
		if (name.compare("Opening") == 0) {
			obj = new Opening();
			target = obj;
		}
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
		objects.push_back(obj);
	}
}

void IntroScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", ToLPCWSTR(scenePath));
	LoadObjects();
	gamemap = new CMap(scenePath);
	gamemap->LoadGameMap();
	CGame* game = CGame::GetInstance();
	if (target != NULL && cam != NULL)
	{
		cam->SetTarget(target);
	}
	DebugOut(L"[INFO] Done loading scene resources %s\n", ToLPCWSTR(scenePath));
}

void IntroScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];
	objects.clear();
	effects.clear();
	target = NULL;
	DebugOut(L"[INFO] Scene %s unloaded! \n", ToLPCWSTR(scenePath));
	isUnload = false;
}

void IntroScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	cam->Update(dt);
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->CollisionUpdate(dt, &coObjects);
	}
	cam->FinalUpdate(dt);
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
	if (isUnload == true)
		CGame::GetInstance()->SwitchScene(WORLD_MAP);
}

void IntroScene::Render()
{
	CGame::GetInstance()->SetViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gamemap->Render();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();

	}
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}
}

int IntroScene::GetSceneType()
{
	return INTRO_SCENE;
}
