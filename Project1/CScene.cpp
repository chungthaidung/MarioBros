#include "CScene.h"
CScene::CScene(int id, std::string path)
{
	this->id = id;
	this->scenePath = path;

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
