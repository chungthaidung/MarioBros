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
#include "Grid.h"
//using namespace std;
using namespace rapidjson;

CPlayScene::CPlayScene(int id,std::string Path,long ptime) :
	CScene(id, Path)
{
	key_handler = new CPlayScenceKeyHandler(this);
	timestart = ptime;
	playtime = ptime;
	player = NULL;
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

void CPlayScene::LoadGridData()
{
	TiXmlDocument doc(scenePath.c_str());
	if (doc.LoadFile()) 
	{
		TiXmlElement* root = doc.RootElement();
		root=root->FirstChildElement("properties");
		int cellwidth=384, cellheight=288, row=0, column=0;
		for (TiXmlElement* property = root->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
		{
			string name = property->Attribute("name");
			if (name.compare("CellHeight") == 0)
				property->QueryIntAttribute("value", &cellheight);
			else if (name.compare("CellWidth") == 0)
				property->QueryIntAttribute("value", &cellwidth);
			else if (name.compare("TotalColumn") == 0)
				property->QueryIntAttribute("value", &column);
			else if (name.compare("TotalRow") == 0)
				property->QueryIntAttribute("value", &row);
		}
		grid= new Grid(cellwidth, cellheight, row, column);
		DebugOut(L"[INFO] cellwidth: %d | cellheight: %d | row: %d | height: %d.\n", cellwidth, cellheight, row, column);
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
			//obj = new CMario();?
			
			obj = new CMario(x, y);
			player = (CMario*)obj; 
			if (player != NULL)
			{
				DebugOut(L"[ERROR] MARIO object was created before!\n");
				//continue;
			}
			if (CGame::GetInstance()->GetMario() != NULL) {
				player->SetLevel(CGame::GetInstance()->GetMario()->GetLevel());
				player->endgame_reward = CGame::GetInstance()->GetMario()->endgame_reward;
			}
			DebugOut(L"[INFO] Player object created!\n");
		}
		else if (name.compare("Ground")==0)
		{
			obj = new CGround();
			SpawnObject(obj, objdata);
		}
		else if (name.compare("Ghost")==0) {
			obj = new GhostObject();
			SpawnObject(obj, objdata);
		}
		else if (name.compare("Enemies") == 0) {
			string enemy = objdata->Attribute("name");
			if (enemy.compare("Goomba") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GOOMBA, state=GOOMBA_STATE_WALKING;
				if (type.compare("Goomba") == 0)
					typeint = GOOMBA;
				else if (type.compare("RedGoomba") == 0)
					typeint = RED_GOOMBA;
				obj = new Goomba(typeint);
				SpawnObject(obj, objdata);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("state") == 0)
					{
						property->QueryIntAttribute("value", &state);
						break;
					}
				}
				obj->SetState(state);
			}
			else if (enemy.compare("Koopa") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_KOOPA, state=KOOPA_STATE_WALKING;
				if (type.compare("Koopas") == 0)
					typeint = GREEN_KOOPA;
				else if (type.compare("RedKoopas") == 0)
					typeint = RED_KOOPA;
				obj = new Koopa(typeint);
				SpawnObject(obj, objdata);
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("state") == 0)
					{
						property->QueryIntAttribute("value", &state);
						break;
					}
				}
				obj->SetState(state);
			}
			else if (enemy.compare("Piranha") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_TYPE, ny=1;
				if (type.compare("Venus") == 0)
					typeint = GREEN_TYPE;
				else if (type.compare("RedVenus") == 0)
					typeint = RED_TYPE;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("ny") == 0)
					{
						property->QueryIntAttribute("value", &ny);
						break;
					}
				}
				obj = new Piranha(typeint,ny,y);
				SpawnObject(obj, objdata);
			}
			else if (enemy.compare("Venus") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = GREEN_TYPE,ny=1;
				if (type.compare("Venus") == 0)
					typeint = GREEN_TYPE;
				else if (type.compare("RedVenus") == 0)
					typeint = RED_TYPE;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("ny") == 0)
					{
						property->QueryIntAttribute("value", &ny);
						break;
					}
				}
				obj = new Venus(typeint,ny,y);
				SpawnObject(obj, objdata);
			}
			else if(enemy.compare("FloatingKoopa") == 0)
			{
				TiXmlElement* property = objdata->FirstChildElement("properties");
				float t_limit=0, b_limit=0;
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("y_limit") == 0)
					{
						string y_limit = property->Attribute("value");
						vector<string> b = ParseComa(y_limit);
						t_limit = stof(b[0]);
						b_limit = stof(b[1]);
						break;
					}
				}				
				obj = new FloatingKoopa(t_limit,b_limit);
				SpawnObject(obj, objdata);
			}
		}
		else if (name.compare("Misc") == 0)
		{
			string misc = objdata->Attribute("name");
			if (misc.compare("Coin") == 0)
			{
				obj = new Coin();
				SpawnObject(obj, objdata);
			}
			else if (misc.compare("QuestionBox") == 0)
			{
				int r=6;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("Reward") == 0)
					{
						property->QueryIntAttribute("value", &r);
						break;
					}
				}
				obj = new QuestionBox(r,y);
				SpawnObject(obj, objdata);
			}
			else if (misc.compare("Brick") == 0)
			{
				string type = objdata->Attribute("type");
				int typeint = BRICK_REWARD, r=6;
				if (type.compare("Brick") == 0)
					typeint = BRICK_BREAKABLE;
				else if (type.compare("QuestionBlock") == 0)
					typeint = BRICK_REWARD;
				TiXmlElement* property = objdata->FirstChildElement("properties");
				for (property = property->FirstChildElement("property"); property != NULL; property = property->NextSiblingElement("property"))
				{
					string name = property->Attribute("name");
					if (name.compare("Reward") == 0)
					{
						property->QueryIntAttribute("value", &r);
						break;
					}
				}
				obj = new Brick(r, typeint, y);
				SpawnObject(obj, objdata);
			}
			else if (misc.compare("EndGameReward") == 0)
			{
				obj = new EndGameReward();
				SpawnObject(obj, objdata);
			}
			else if (misc.compare("MovingObject") == 0)
			{
				obj = new MovingObject();
				SpawnObject(obj, objdata);
			}
		}
		else if (name.compare("Teleport") == 0)
		{
			obj = new Teleport(objdata);
			SpawnObject(obj, objdata);
		}
		else if (name.compare("Portal") == 0)
		{
			obj = new Portal(objdata);
			SpawnObject(obj, objdata);
		}
		objdata->QueryFloatAttribute("width", &width);
		objdata->QueryFloatAttribute("height", &height);
		obj->SetWidthHeight(width, height);
		obj->SetPosition(x, y);
		//DebugOut(L"[INFO]Object x: %d || y: %d || width: %f || height: %f. \n",x,y,width,height);
		//objects.push_back(obj);
	}
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", ToLPCWSTR(scenePath));
	LoadGridData();
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
	//int size = grid->GetCell(1, 3)->GetListObj().size();
	//DebugOut(L"[GRID SIZE] GRID CELL (1,3) : %d\n", size);
	DebugOut(L"[INFO] Done loading scene resources %s\n", ToLPCWSTR(scenePath));
	Update(1);
}

void CPlayScene::Update(DWORD dt)
{
	if (isUnload == true)
		return;
	if (player == NULL) return;
	if(delaytime<=0 ){
		cam->Update(dt);
		//DebugOut(L"[INFO MARIO LEVEL] Mario level : %d\n", CGame::GetInstance()->GetMario()->GetLevel());
		listObjects.clear();
		//vector<CGameObject*> obj = FindGlobalObjectInCam();
		unordered_set<CGameObject*> gridobjs = grid->GetObjectsByCam(cam);
		for (auto v : gridobjs) {
			listObjects.push_back(v);
		}
		listObjects.insert(listObjects.end(), objectswithoutgrid.begin(), objectswithoutgrid.end());
		//listObjects.insert(listObjects.end(), obj.begin(), obj.end());
		//DebugOut(L"[INFO OBJECT] List Object size: %d \n", listObjects.size());
		vector<LPGAMEOBJECT> coObjects;
		for (size_t i = 0; i < listObjects.size(); i++)
		{
			coObjects.push_back(listObjects[i]);
		}		
		//DebugOut(L"[EFFECT INFO1] Object SIZE: %d \n", objects.size());
		float cx = cam->position.x;
		float cy = cam->position.y;
		hud->Update(dt);
		
		player->Update(dt);
		for (size_t i = 0; i < listObjects.size(); i++)
		{
			//if(listObjects[i]->isRemove==false)
			listObjects[i]->Update(dt);
		}

		coObjects.push_back(player);
		player->CollisionUpdate(dt, &coObjects);
		for (size_t i = 0; i < listObjects.size(); i++)
		{
			//if (listObjects[i]->isRemove == false)
				listObjects[i]->CollisionUpdate(dt, &coObjects);
		}

		cam->FinalUpdate(dt);
		player->FinalUpdate(dt);
		for (size_t i = 0; i < listObjects.size(); i++)
		{
			if (player == NULL) break;
			listObjects[i]->FinalUpdate(dt);
		}
		for (size_t i = 0; i < effects.size(); i++)
		{
			effects[i]->Update(dt);
		}
		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		//RemoveEffects();
		//RemoveListObject();
		//RemoveObjectsWithoutGrid();
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

	RemoveObjectsWithoutGrid();
}

void CPlayScene::Render()
{
	if (isUnload == true)
		return;
	CGame::GetInstance()->SetViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
	vector<CGameObject*> renderorder;
	renderorder.insert(renderorder.end(), listObjects.begin(), listObjects.end());

	std::sort(renderorder.begin(), renderorder.end(), CGameObject::rendercompare);
	for (int i = 0; i < renderorder.size() && renderorder[i]->renderOrder < 2; i++)
	{
		if (renderorder[i]->isRemove == false)
			renderorder[i]->Render();
	}
	gamemap->Render();
	for (int i = 0; i < renderorder.size(); i++)
	{
		if (renderorder[i]->renderOrder >= 2 && renderorder[i]->isRemove == false)
			renderorder[i]->Render();
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
	for (int i = 0; i < objectswithoutgrid.size(); i++)
		delete objectswithoutgrid[i];
	for (int i = 0; i < effects.size(); i++)
		delete effects[i];
	//listObjects.clear();
	objectswithoutgrid.clear();
	effects.clear();
	//cam = NULL;
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
				grid->Add(obj,x, y);
			}
			document.Clear();
			break;
		}
	}
}

void CPlayScene::RemoveListObject()
{
	listObjects.erase(remove_if(listObjects.begin(), listObjects.end(), [](CGameObject* obj) {
		if (obj->isRemove) {
			if (obj->canDelete) delete obj;
			return true;
		}
		return false;
		}), listObjects.end());
}

vector<CGameObject*> CPlayScene::FindGlobalObjectInCam()
{
	vector<CGameObject*> obj;
	float cx = cam->position.x;
	float cy = cam->position.y;
	for (int i = 0; i < objectswithoutgrid.size(); i++)
	{
		if ((objectswithoutgrid[i]->GetPosition().x< cx - cam->size.x / 2 || objectswithoutgrid[i]->GetPosition().x > cx + cam->size.x * 3 / 2
			|| objectswithoutgrid[i]->GetPosition().y < cy - cam->size.y / 2 || objectswithoutgrid[i]->GetPosition().y > cy + cam->size.y * 3 / 2))
			obj.push_back(objectswithoutgrid[i]);
		else if (objectswithoutgrid[i]->GetObjectType() == OBJECT_TYPE_TAIL || objectswithoutgrid[i]->GetObjectType() == OBJECT_TYPE_FIREBALL)
		{
			obj.push_back(objectswithoutgrid[i]);
		}
	}
	return obj;
}


