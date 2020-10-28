#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Mario.h"

class CMario;
class PlayerLevel
{
protected:
	CMario* mario;
public:
	PlayerLevel(CMario* mario);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render()=0;
	virtual void SetState(int state);

	virtual void Collision(vector<LPGAMEOBJECT>* colliable_objects);
	virtual void MovingState(DWORD dt);
	virtual void JumpingState(DWORD dt);
	//virtual void CrouchState(DWORD dt)=0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)=0;
};

