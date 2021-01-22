#include "Grid.h"

Grid::Grid(float width, float height, int row, int column)
{
	cellWidth = width;
	cellHeight = height;
	this->row = row;
	this->column = column;
	
	//Nhớ kỹ thứ tự duyệt này nha, cells[column][row]
	//ok huhuhuuh nãy tui làm row trc @@ lú quá
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
	cells[x][y]->Add(obj);
}

vector<Cell*> Grid::GetCellsByCam(Camera* cam)
{
	vector<Cell*> cellbycam;
	cellbycam.clear();
	int begincolumn = (int)cam->position.x / cellWidth;
	int beginrow = (int)cam->position.y / cellHeight;
	int endcolumn = (int)ceil((cam->position.x + cam->size.x) / cellWidth);
	int endrow = (int)ceil((cam->position.y + cam->size.y) / cellHeight);

	begincolumn = max(0, begincolumn);
	beginrow = max(0, beginrow);
	endcolumn = min(endcolumn, column);
	endrow = min(endrow, row);

	for (int i = begincolumn; i < endcolumn; i++)
	{
		for (int j = beginrow; j < endrow; j++)
		{
			cellbycam.push_back(cells[i][j]);
		}
	}
	return cellbycam;
}

vector<CGameObject*> Grid::GetObjectsByCam(Camera* cam)
{
	vector<CGameObject*> objects;
	objects.clear();
	vector<Cell*> activeCell = GetCellsByCam(cam);

	for (int i = 0; i < activeCell.size(); i++)
	{
		vector<CGameObject*> temp = activeCell[i]->GetListObj();
		for (int j = 0; j < temp.size(); j++)
		{
			if (temp[j]->isRemove == true) continue;
			objects.push_back(temp[j]);
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


