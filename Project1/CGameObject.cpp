#include <d3dx9.h>
#include <algorithm>

#include "debug.h"
#include "CGame.h"
#include "CGameObject.h"
#include "CSprites.h"
#include "CAnimation.h"
#include "CAnimations.h"
#include "CTextures.h"	
#include "GhostObject.h"
#include "CCollisionEvent.h"
bool CGameObject::rendercompare(CGameObject*& a, CGameObject*& b)
{
	return a->renderOrder < b->renderOrder ;
}
CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;
	isRemove = false;
}

D3DXVECTOR2 CGameObject::GetWidthHeight()
{

	return D3DXVECTOR2(width,height);
}

void CGameObject::Update(DWORD dt)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

void CGameObject::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CGameObject::FinalUpdate(DWORD dt)
{
}

void CGameObject::SetState(int state)
{
	this->state = state;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny,touchingLength;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny, touchingLength
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, touchingLength, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		
		if (c->obj->GetObjectType()==OBJECT_TYPE_GHOST&& (c->ny > 0||c->nx!=0)) continue;
		if (c->obj->GetObjectType() == OBJECT_TYPE_COIN ) continue;
		if (c->obj->GetState()==BRICK_COIN && c->obj->GetObjectType() == OBJECT_TYPE_BRICK ) continue;
		//if (c->obj->GetObjectType() == OBJECT_TYPE_SUPER_MUSHROOM ) continue;
		if (c->obj->GetObjectType() == OBJECT_TYPE_END_GAME_REWARD ) continue;
		//if (c->obj->GetObjectType() == OBJECT_TYPE_MARIO && c->nx != 0 && GetObjectType() != OBJECT_TYPE_COIN && GetObjectType() != OBJECT_TYPE_KOOPA && GetState() != KOOPA_STATE_CROUCH) continue;
		if (GetObjectType() == OBJECT_TYPE_SUPER_MUSHROOM)
		{
			if (c->obj->isEnemy == true) continue;
		}
		if (GetObjectType() == OBJECT_TYPE_VENUS_FIREBALL)
		{
			if (c->obj->GetObjectType() == OBJECT_TYPE_MARIO) continue;
		}
		if (c->obj->isEnemy == true)
		{
			if (GetObjectType() == OBJECT_TYPE_SUPER_MUSHROOM || GetObjectType() == OBJECT_TYPE_SUPER_LEAF) continue;
			if (GetObjectType() == OBJECT_TYPE_VENUS_FIREBALL) continue;
		}
		//if (c->obj->GetObjectType() == OBJECT_TYPE_MARIO && c->nx!=0 && GetObjectType() != OBJECT_TYPE_KOOPA && GetState()!=KOOPA_STATE_CROUCH) continue;
		//c->obj continue
		//if (c->obj->GetObjectType() == OBJECT_TYPE_QUESTION_BOX) DebugOut(L"[FILTER] Question box \n");

		if (c->t < min_tx && c->nx != 0 ) {//&& c->nx*vx<0
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i; 
			rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {//&&c->ny * vy < 0
			min_ty = c->t;
			ny = c->ny; 
			min_iy = i; 
			rdy = c->dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) {
		LPCOLLISIONEVENT c = coEvents[i];
		if (c->nx != 0 && c->t == min_tx)
			coEventsResult.push_back(c);
		if (c->ny != 0 && c->t == min_ty)
			coEventsResult.push_back(c);
	}
	//if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	//if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


D3DXVECTOR2 CGameObject::GetPosition()
{
	return D3DXVECTOR2(x,y);
}

void CGameObject::Setny(int a)
{
	ny = a;
}

int CGameObject::Getny()
{
	return ny;
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(0, 0, 0);
	RECT rect;
	
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, bbox, rect,p, 32);//hardcode
}


CGameObject::~CGameObject()
{
	DebugOut(L"Da xoa object\n");
}