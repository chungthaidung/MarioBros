#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Cell::Add(CGameObject* obj)
{
	listobj.insert(obj);
}

unordered_set<CGameObject*> Cell::GetListObj()
{
		return listobj;
}

void Cell::RemoveObj(CGameObject* obj)
{
	auto find = listobj.find(obj);
	if (find == listobj.end())
		return;
	listobj.erase(obj);
}

void Cell::Clear()
{
	for (auto t: listobj)
		delete t;
	listobj.clear();
}

void Cell::GetIndex(int& x, int& y)
{
	x = this->x;
	y = this->y;
}
