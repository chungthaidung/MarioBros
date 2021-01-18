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
}
void MarioTail::Moving(DWORD dt)
{
	x = mario->x + (MARIO_RACOON_BBOX_WIDTH - MARIO_TAIL_BBOX_WIDTH) / 2;
	y = mario->y + (MARIO_RACOON_BBOX_HEIGHT - MARIO_TAIL_BBOX_HEIGHT) / 2;
	//DebugOut(L"Tail x: %f, tail y: %f\n", x, y);
	if (!active) {
		vx = 0;
		return;
	}
	int attackState = 1;
	//int attackState = (GetTickCount() - attackStart <= 125) ? -1 : 1;
	if (GetTickCount() - attackStart <= 125) attackState = -1;
	else attackState = 1;
	nx = mario->Getnx();
	vy = 0;
	vx = 3.5 * mario->Getnx() * attackState;
}
int MarioTail::GetObjectType()
{
	return 21;
}
bool MarioTail::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_GHOST && (direction.y > 0 || direction.x != 0))
		return true;
	if (obj->GetObjectType() == OBJECT_TYPE_COIN)
		return true;
	if (obj->GetState() == BRICK_COIN && obj->GetObjectType() == OBJECT_TYPE_BRICK) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_END_GAME_REWARD) return true;
	return false;
}
void MarioTail::SetActive(bool a)
{
	if (!active && a) {
		//Bat dau danh
		attackStart = GetTickCount();
	}
	active = a;
}
