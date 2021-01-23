#pragma once
#include "Cell.h"
#include "Camera.h"
class Grid
{
protected:
	float cellWidth, cellHeight;
	int row, column;
	Cell*** cells;
public:
	Grid(float width, float height, int row, int column);
	~Grid();
	virtual void Add(CGameObject* obj, int x, int y);
	virtual vector<Cell*> GetCellsByCam(Camera* cam);
//	virtual vector<CGameObject*> GetObjectsByCam(Camera* cam);
	virtual unordered_set<CGameObject*> GetObjectsByCam(Camera* cam);
	virtual Cell* GetCell(int x,int y);
	virtual Cell* GetCellByPosition(D3DXVECTOR2 pos);
	virtual void ClearAll();
};

