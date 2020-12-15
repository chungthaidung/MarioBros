#pragma once
#include <d3dx9.h>
#include <d3d9.h>
class Brick;
class BrokenBrick
{
public:
	BrokenBrick(Brick* obj);
	~BrokenBrick();
	void Update(DWORD dt);
	void Render();
protected:
	Brick* brick;
	float x, y,vx,vy;
};

