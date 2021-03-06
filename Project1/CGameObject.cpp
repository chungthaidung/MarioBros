﻿#include <d3dx9.h>
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
#include "Mario.h"
#include "CheckPoint.h"
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
	float sl, st, sr, sb;
	float ml, mt, mr, mb;
	float t, rnx, rny, touchingLength;
	this->GetBoundingBox(ml, mt, mr, mb);

	coEventsResult.clear();

	for (LPCOLLISIONEVENT c : coEvents)
	{
		for (LPCOLLISIONEVENT cr : coEventsResult)
		{
			float dx = c->dx;
			float dy = c->dy;
			if (c->nx != 0) {
				dy = dy * cr->t + (c->dy > 0 ? -1 : 1) * 0.02f;
			}
			else {
				dx = dx * cr->t + (c->dx > 0 ? -1 : 1) * 0.02f;
			}
			c->obj->GetBoundingBox(sl, st, sr, sb);
			CGame::SweptAABB(ml, mt, mr, mb, dx, dy, sl, st, sr, sb, t, rnx, rny, touchingLength);
			if (t <= 0 || t > 1) {
				c->t = t;
			}
		}
		if (c->t > 0 && c->t <= 1) {
			coEventsResult.push_back(c);
		}
	}

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;


	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT c = coEventsResult[i];

		D3DXVECTOR2 direction = D3DXVECTOR2(c->nx, c->ny);
		if (GetThrough(c->obj, direction)) continue;

		if (c->t < min_tx && c->nx != 0 ) {
			min_tx = c->t; 
			nx = c->nx; 
			min_ix = i; 
			rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t;
			ny = c->ny; 
			min_iy = i; 
			rdy = c->dy;
		}
	}
	/*for (UINT i = 0; i < coEventsResult.size(); i++) {
		LPCOLLISIONEVENT c = coEventsResult[i];
		if (c->nx != 0 && c->t == min_tx)
			coEventsResult.push_back(c);
		if (c->ny != 0 && c->t == min_ty)
			coEventsResult.push_back(c);
	}*/
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
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CGame::GetInstance()->DrawEx(x-cx, y-cy, bbox, rect,p, 1, D3DXVECTOR2(1.0f, 1.0f), 32);
}


CGameObject::~CGameObject()
{
	DebugOut(L"Da xoa object\n");
}