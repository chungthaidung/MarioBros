#include "CScene.h"
#include "debug.h"
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
