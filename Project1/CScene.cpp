#include "CScene.h"
CScene::CScene(int id,std::string mapPath, LPCWSTR filePath)
{
	this->id = id;
	this->sceneMapPath = mapPath;
	this->sceneFilePath = filePath;
}