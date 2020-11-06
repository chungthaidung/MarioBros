#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Mario.h"

class CMario;
class PlayerLevel
{
protected:
	CMario* mario;
	D3DXVECTOR2 collisionbox;
public:
	PlayerLevel(CMario* mario);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render()=0;
	virtual void SetState(int state);

	virtual void MiniJump(DWORD dt);
	virtual void Collision(vector<LPGAMEOBJECT>* colliable_objects);
	virtual void PowerMeterUpdate(DWORD dt);
	virtual void MovingState(DWORD dt);
	virtual void JumpingState(DWORD dt);
	virtual void CrouchState(DWORD dt) {};
	virtual void AttackState(DWORD dt) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)=0;
	virtual void SetCollisionBox(float x, float y) { collisionbox.x = x; collisionbox.y = y; }

	D3DXVECTOR2 GetCollisionBox() { return collisionbox; }
	virtual void OnKeyDown(int KeyCode) {};
	
};

