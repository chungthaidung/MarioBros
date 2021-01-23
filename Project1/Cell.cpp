#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Cell::Add(CGameObject* obj)
{
	listobj.insert(obj);
	//listobj.push_back(obj);
}

//vector<CGameObject*> Cell::GetListObj()
//{
//	vector<CGameObject*> list;
//	
//	return list;
//}

unordered_set<CGameObject*> Cell::GetListObj()
{
		return listobj;
}

void Cell::Clear()
{
	for (auto t: listobj)
		delete t;
	listobj.clear();
}
