#include "MarioFireBall.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
MarioFireBall::MarioFireBall(CMario* p)
{
	p = mario;

}
void MarioFireBall::Render()
{
	CAnimations::GetInstance()->Get(MARIO_ANI_FIRE_BALL)->Render(x, y);
	RenderBoundingBox();
}
void MarioFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_FIRE_BALL_BBOX_WIDTH ;
	b = y + MARIO_FIRE_BALL_BBOX_HEIGHT;
}
void MarioFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += FIREBALL_GRAVITY * dt;
	vx = FIREBALL_SPEED*nx;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x > cx + SCREEN_WIDTH || x < cx)
		active = false;
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx *dx + nx * 0.02f;
		y += min_ty * dy + ny * 0.02f;
		if (nx != 0) { 
			vx = 0; 
			active = false;
		}
		if (ny != 0) vy -= 0.5;
			
	}
	DebugOut(L"COEvents size %d \n", coObjects->size());
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void MarioFireBall::Reset(float mx,float my)
{
	vx = FIREBALL_SPEED * nx;
	x = mx;
	y = my;


}