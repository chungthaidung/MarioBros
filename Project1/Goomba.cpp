#include "Goomba.h"
#include "define.h"
#include "Mario.h"
#include "MarioTail.h"
#include "debug.h"
#include "CCollisionEvent.h"
#include "CGame.h"
#include "FlyingGoomba.h"
Goomba::Goomba(int type)
{
	this->type = type;
	goombaState = new NormalGoomba(this);
	SetState(GOOMBA_STATE_WALKING);
	collision_box.x = GOOMBA_BBOX_WIDTH;
	collision_box.y = GOOMBA_BBOX_HEIGHT;
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x;
	top = y;
	right = x + collision_box.x;
	bottom = y + collision_box.y;*/
	goombaState->GetBoundingBox(left,top,right,bottom);
}
void Goomba::Update(DWORD dt)
{
	
	goombaState->Update(dt);
	//DebugOut(L"vx: %f nx: %d \n", vx,nx);
}
void Goomba::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	goombaState->CollisionUpdate(dt,coObjects);
}
void Goomba::FinalUpdate(DWORD dt)
{
	goombaState->FinalUpdate(dt);
}
void Goomba::Render()
{
	/*int ani = GOOMBA_ANI_WALKING;
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		ani = GOOMBA_ANI_DIE;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y, 1,nx,ny);
	RenderBoundingBox();*/
	goombaState->Render();
}
int Goomba::GetObjectType()
{
	return OBJECT_TYPE_GOOMBA;
}
int Goomba::GetType()
{
	return type;
}
DWORD Goomba::GetDieTime()
{
	return dietime;
}
void Goomba::SetDieTime(DWORD time)
{
	dietime = time;
}
void Goomba::SetState(int state)
{
	CGameObject::SetState(state);
	y += goombaState->GetCollisionBox().y;
	goombaState->SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_WALKING:
		goombaState = new NormalGoomba(this);
		break;
	case GOOMBA_STATE_FLYING:
		goombaState = new FlyingGoomba(this);
		break;
	}
	y -= goombaState->GetCollisionBox().y;
}
