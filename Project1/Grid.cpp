#include "Grid.h"

Grid::Grid(float width, float height, int row, int column)
{
	cellWidth = width;
	cellHeight = height;
	this->row = row;
	this->column = column;

	cells = new Cell * *[column];
	for (int i = 0; i < column; i++)
	{
		cells[i] = new Cell * [row];
		for (int j = 0; j < row; j++)
		{
			cells[i][j] = new Cell(i, j);
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cells[i][j]->Clear();
		}
	}
}

void Grid::Add(CGameObject* obj, int x, int y)
{
	if (x > column-1 || y > row-1 || x < 0 || y < 0)
		return;
	cells[x][y]->Add(obj);
}

void Grid::Move(CGameObject* obj, int x, int y)
{
	cells[x][y]->RemoveObj(obj);
	D3DXVECTOR2 new_pos = obj->GetPosition();
	int new_x = (int)new_pos.x / cellWidth;
	int new_y = (int)new_pos.y / cellHeight;
	Add(obj, new_x, new_y);
}


vector<Cell*> Grid::GetCellsByCam(Camera* cam)
{
	vector<Cell*> cellbycam;
	cellbycam.clear();
	int begincolumn = (int)cam->position.x / cellWidth;
	int beginrow = (int)cam->position.y / cellHeight;
	int endcolumn = (int)ceil((cam->position.x + cam->size.x) / cellWidth);
	int endrow = (int)ceil((cam->position.y + cam->size.y) / cellHeight);

	begincolumn = max(0, begincolumn-1);
	beginrow = max(0, beginrow-1);
	endcolumn = min(endcolumn+1, column);
	endrow = min(endrow+1	, row);

	for (int i = begincolumn; i < endcolumn; i++)
	{
		for (int j = beginrow; j < endrow; j++)
		{
			cellbycam.push_back(cells[i][j]);
		}
	}
	return cellbycam;
}

unordered_set<CGameObject*> Grid::GetObjectsByCam(Camera* cam)
{
	unordered_set<CGameObject*> objects;
	vector<Cell*> activeCell = GetCellsByCam(cam);


	for (int i = 0; i < activeCell.size(); i++)
	{
		int x, y;
		activeCell[i]->GetIndex(x, y);
		float left = x * cellWidth;
		float top = y * cellHeight;
		float right = left + cellWidth;
		float bottom = top + cellHeight;
		auto temp = activeCell[i]->GetListObj();
		for (auto t : temp)
		{
			if (t->isRemove == true) continue;
			float t_l, t_t, t_r, t_b;
			t->GetBoundingBox(t_l, t_t, t_r, t_b);
			if (t_r<= left || t_l>= right || t_t >= bottom || t_b <= top)
			{
				Move(t, x, y);
			}
			objects.insert(t);
		}
	}
	return objects;
}

Cell* Grid::GetCell(int x, int y)
{
	return cells[x][y];
}

Cell* Grid::GetCellByPosition(D3DXVECTOR2 pos )
{
	int x = (int)(pos.x / cellWidth);
	int y = (int)(pos.y / cellHeight);
	return cells[x][y];
}

void Grid::ClearAll()
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cells[i][j]->Clear();
		}
	}
}


