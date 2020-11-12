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
	int ani = MARIO_ANI_FIRE_BALL;
	switch (state)
	{
	case MARIO_FIRE_BALL_STATE_DAMAGED:
		ani = MARIO_ANI_FIRE_BALL_DAMAGED;
		
		break;
	case MARIO_FIRE_BALL_STATE:
		ani = MARIO_ANI_FIRE_BALL;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
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
	vy += gravity * dt;
	CGameObject::Update(dt);
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
		x += min_tx *dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) { 
			vx = 0; 
			vy = 0;
			gravity = 0;
			if (state != MARIO_FIRE_BALL_STATE_DAMAGED) {
				SetState(MARIO_FIRE_BALL_STATE_DAMAGED);
				damagedtime = GetTickCount();
			}
		}
		if (ny != 0) vy -= 0.5;
			
	}
	State(dt);
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void MarioFireBall::Reset(float mx,float my)
{
	SetState(MARIO_FIRE_BALL_STATE);
	gravity = FIREBALL_GRAVITY;
	vx = FIREBALL_SPEED * nx;
	x = mx;
	y = my;
	vy = 0;
}
void MarioFireBall::State(DWORD dt)
{
	switch (state)
	{
	case MARIO_FIRE_BALL_STATE_DAMAGED:
		if (GetTickCount() - damagedtime > 130) {
			active = false;
		}
		break;
	}
}