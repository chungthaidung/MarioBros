#include "VenusFireBall.h"
#include "CGame.h"
#include "Venus.h"
#include "debug.h"
#include "define.h"
VenusFireBall::VenusFireBall(Venus* v)
{
	venus = v;
	canDelete = false;
	active = false;
	vx = VENUS_FIRE_BALL_VELOCITY;
	vy = VENUS_FIRE_BALL_VELOCITY;
	isEnemy = true;
}

void VenusFireBall::Update(DWORD dt)
{
	CGameObject::Update(dt);	
	//DebugOut(L"x: %f, y: %f\n", x, y);
}

void VenusFireBall::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void VenusFireBall::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	float cx, cy;
	cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	//CGame::GetInstance()->GetCamPos(cx, cy);
	if (x > cx + SCREEN_WIDTH || x < cx)
	{
		active = false;
		isRemove = true;
	}
	if (y > cy + CGame::GetInstance()->GetScreenHeight() || y < cy)
	{
		active = false;
		isRemove = true;
	}
	// No collision occured, proceed normally
	x += dx;
	y += dy;
	if (coEResult.size() == 0)
	{
		
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

	}
	for (UINT i = 0; i < coEResult.size(); i++) {
		delete coEResult[i];
	}
	coEResult.clear();
}

void VenusFireBall::Render()
{
	int ani = MARIO_ANI_FIRE_BALL;
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}

void VenusFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + VENUS_FIRE_BALL_BBOX_WIDTH;
	b = y + VENUS_FIRE_BALL_BBOX_HEIGHT;
}

void VenusFireBall::Reset(float start_x, float start_y, float mx, float my)
{
	if (venus != NULL) {
		nx = venus->Getnx();
		if (venus->GetHead() == VENUS_HEAD_UP)
			vy = -VENUS_FIRE_BALL_VELOCITY *my;
		else if (venus->GetHead() == VENUS_HEAD_DOWN)
			vy = VENUS_FIRE_BALL_VELOCITY *my;
		vx = VENUS_FIRE_BALL_VELOCITY * nx*mx;
		x = start_x;
		y = start_y;
	}
}

int VenusFireBall::GetObjectType()
{
	return OBJECT_TYPE_VENUS_FIREBALL;
}

bool VenusFireBall::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	return false;
}

void VenusFireBall::SetActive(bool a)
{
	active = a;
}

bool VenusFireBall::GetActive()
{
	return active;
}
