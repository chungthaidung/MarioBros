#include "CScene.h"
#include "debug.h"
#include "CGame.h"
CScene::CScene(int id, std::string path)
{
	this->id = id;
	this->scenePath = path;

}

void CScene::RemoveObjects()
{
	objects.erase(remove_if(objects.begin(), objects.end(), [](CGameObject* obj) {
		if (obj->isRemove) {
			if (obj->canDelete) delete obj;
			return true;
		}
		return false;
		}), objects.end());
}

void CScene::SpawnObject(CGameObject* obj)
{
	obj->isRemove = false;
	objects.push_back(obj);
	//DebugOut(L"ADD thanh cong \n");
}
void CScene::DespawnObject(CGameObject* obj)
{
	obj->isRemove = true;
}

void CScene::SpawnObject(CGameObject* obj, TiXmlElement* data)
{
}

void CScene::RemoveObjectsWithoutGrid()
{
	objectswithoutgrid.erase(remove_if(objectswithoutgrid.begin(), objectswithoutgrid.end(), [](CGameObject* obj) {
		if (obj->isRemove) {
			if (obj->canDelete) delete obj;
			return true;
		}
		return false;
		}), objectswithoutgrid.end());
}

void CScene::SpawnObjectWithoutGrid(CGameObject* obj)
{
	obj->isRemove = false;
	auto find = std::find(objectswithoutgrid.begin(), objectswithoutgrid.end(), obj);
	if (find == objectswithoutgrid.end())
		objectswithoutgrid.push_back(obj);
}

void CScene::RemoveEffects()
{
	effects.erase(remove_if(effects.begin(), effects.end(), [](LPEFFECT ef) {
		if (ef->isRemove) {
			if (ef->canDelete) delete ef;
			return true;
		}
		return false;
		}), effects.end());
}

void CScene::AddEffect(LPEFFECT ef)
{
	ef->isRemove = false;
	effects.push_back(ef);
}

void CScene::DeleteEffect(LPEFFECT ef)
{
	ef->isRemove = true;
}

void CScene::ClearScene()
{
	RemoveEffects();
	RemoveObjectsWithoutGrid();
	if (isUnload == true)
		CGame::GetInstance()->SwitchScene(switchsceneid);
}

Camera* CScene::GetCamera()
{
	return cam;
}

CMap* CScene::GetMap()
{
	return gamemap;
}

long CScene::GetPlayTime()
{
	return playtime;
}

void CScene::SetisUnload(bool a)
{
	isUnload = a;
}

void CScene::SetSwitchScene(int a)
{
	switchsceneid = a;
}

void CScene::SetBoundary(RECT a)
{
	cam_boundary = a;
}

RECT CScene::GetBoundary()
{
	return cam_boundary;
}
