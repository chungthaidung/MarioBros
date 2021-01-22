#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Cell::Add(CGameObject* obj)
{
	listobj.push_back(obj);
}

vector<CGameObject*> Cell::GetListObj()
{
	return listobj;
}

void Cell::Clear()
{
	for (int i = 0; i < listobj.size(); i++)
		delete listobj[i];
	listobj.clear();
}
