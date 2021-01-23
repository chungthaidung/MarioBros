#pragma once
#include "CGameObject.h"
#include <unordered_set>
class Cell
{
protected:
	int x, y;
	unordered_set<CGameObject*> listobj;
public:
	Cell(int x, int y);
	virtual void Add(CGameObject* obj);
	unordered_set<CGameObject*> GetListObj();
	virtual void RemoveObj(CGameObject* obj);
	virtual void Clear();
	virtual void GetIndex(int& x, int& y);
};