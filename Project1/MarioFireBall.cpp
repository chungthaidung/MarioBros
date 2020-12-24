#include "MarioFireBall.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
#include "debug.h"
#include "FireBallEf.h"
MarioFireBall::MarioFireBall(CMario* p)
{
	mario = p;
	canDelete = false;
}
void MarioFireBall::Render()
{
	int ani = MARIO_ANI_FIRE_BALL;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}
void MarioFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_FIRE_BALL_BBOX_WIDTH ;
	b = y + MARIO_FIRE_BALL_BBOX_HEIGHT;
}
void MarioFireBall::Update(DWORD dt)
{
	vy += gravity * dt;
	vx = FIREBALL_SPEED * nx;
	CGameObject::Update(dt);

}
void MarioFireBall::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}
void MarioFireBall::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	float cx, cy;
	cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	if (x > cx + SCREEN_WIDTH || x < cx)
	{
		active = false;
		isRemove = true;
	}
	// No collision occured, proceed normally
	if (coEResult.size() == 0)
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
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) {
			vy = 0;
			vx = 0;
			gravity = 0;
			FireBallEf* effect = new FireBallEf();
			effect->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddEffect(effect);
			active = false;
			isRemove = true;
		}
		if (ny != 0) { 
			vy = -FIREBALL_JUMP_FORCE; 
		}

	}
	for (UINT i = 0; i < coEResult.size(); i++) {
		delete coEResult[i];
	}
	coEResult.clear();
}
void MarioFireBall::Reset(float mx,float my)
{
	if (mario != NULL) {
		
		gravity = FIREBALL_GRAVITY;
		vx = FIREBALL_SPEED * nx;
		x = mx;
		y = my;
		vy = 0;
		nx = mario->Getnx();
	}
}
int MarioFireBall::GetObjectType()
{
	return OBJECT_TYPE_FIREBALL;
}
