#pragma once
class CGameObject;
class CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

class CCollisionEvent
{
public:
	CGameObject* obj;
	float t, nx, ny;
	float dx, dy;		// *RELATIVE* movement distance between this object and obj
	float touchingLength;
	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0,float touchingLength=0, CGameObject* obj = nullptr);
	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b);
};