#include "CCollisionEvent.h"
#include "CGameObject.h"

CCollisionEvent::CCollisionEvent(float t, float nx, float ny, float dx, float dy,float touchingLength, CGameObject* obj)
{
	this->t = t;
	this->nx = nx;
	this->ny = ny;
	this->dx = dx;
	this->dy = dy;
	this->obj = obj;
	this->touchingLength = touchingLength;
}

bool CCollisionEvent::compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
{
	return a->t < b->t;
}
