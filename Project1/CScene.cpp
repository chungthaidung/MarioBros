#include "CScene.h"
CScene::CScene(int id, LPCWSTR mapPath, LPCWSTR filePath)
{
	this->id = id;
	this->mapFilePath = mapPath;
	this->sceneFilePath = filePath;
}

void CScene::RemoveObjects()
{
	objects.erase(remove_if(objects.begin(), objects.end(), [](CGameObject* obj) {
		return obj->isRemove;
		}), objects.end());
}

void CScene::SpawnObject(CGameObject* obj)
{
	obj->isRemove = false;
	objects.push_back(obj);
}

void CScene::DespawnObject(CGameObject* obj)
{
	obj->isRemove = true;
}
