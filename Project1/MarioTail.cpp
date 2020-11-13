#include "MarioTail.h"
#include "define.h"
#include "CGame.h"
#include "debug.h"

MarioTail::MarioTail(CMario* p)
{
	mario = p;
}
void MarioTail::Render()
{
	RenderBoundingBox();
}
void MarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_TAIL_BBOX_WIDTH;
	b = y + MARIO_TAIL_BBOX_HEIGHT;
}
void MarioTail::Update(DWORD dt)
{
	Moving(dt);
	CGameObject::Update(dt);
	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;
	//coEvents.clear();
	//CalcPotentialCollisions(coObjects, coEvents);
	//// No collision occured, proceed normally
	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny;
	//	float rdx = 0;
	//	float rdy = 0;
	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	//	x += min_tx * dx + nx * 0.4f;
	//	y += min_ty * dy + ny * 0.4f;
	//
	//}
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void MarioTail::Moving(DWORD dt)
{
	x = mario->x + (MARIO_RACOON_BBOX_WIDTH - MARIO_TAIL_BBOX_WIDTH) / 2;
	y = mario->y + (MARIO_RACOON_BBOX_HEIGHT - MARIO_TAIL_BBOX_HEIGHT) / 2;

	if (!active) {
		vx = 0;
		return;
	}
	int attackState = 1;
	//int attackState = (GetTickCount() - attackStart <= 125) ? -1 : 1;
	if (GetTickCount() - attackStart <= 125) attackState = -1;
	else attackState = 1;
	vy = 0;
	vx = 3 * mario->Getnx() * attackState;
}

int MarioTail::GetObjectType()
{
	return 21;
}



void MarioTail::SetActive(bool a)
{
	if (!active && a) {
		//Bat dau danh
		attackStart = GetTickCount();
	}
	active = a;
}
