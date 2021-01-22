#pragma once
#include "CGameObject.h"
#include <unordered_set>
class Cell
{
protected:
	int x, y;
	vector<CGameObject*> listobj;
public:
	Cell(int x, int y);
	virtual void Add(CGameObject* obj);
	vector<CGameObject*> GetListObj();
	virtual void Clear();
};