#include "CScene.h"
CScene::CScene(int id, LPCWSTR mapPath, LPCWSTR filePath)
{
	this->id = id;
	this->mapFilePath = mapPath;
	this->sceneFilePath = filePath;
}