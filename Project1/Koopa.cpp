#include "Koopa.h"
#include "define.h"
#include "Mario.h"
#include "MarioTail.h"
#include "debug.h"
#include "WalkingKoopa.h"
#include "CrouchKoopa.h"
#include "RunningShell.h"
#include "CCollisionEvent.h"
Koopa::Koopa()
{
	koopaState = new WalkingKoopa(this);
	state = KOOPA_STATE_WALKING;
}
void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + koopaState->GetCollisionBox().x;
	bottom = y + koopaState->GetCollisionBox().y;

}
void Koopa::Update(DWORD dt)
{
	koopaState->Update(dt);
	//DebugOut(L"KOOPA VY: %f \n", vy);
}
void Koopa::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	koopaState->CollisionUpdate(dt, coObjects);
}
void Koopa::FinalUpdate(DWORD dt)
{
	koopaState->FinalUpdate(dt);
}
void Koopa::Render()
{
	koopaState->Render();
}
int Koopa::GetObjectType()
{
	return OBJECT_TYPE_KOOPA;
}
void Koopa::SetGravity(float a)
{
	gravity = a;
}
float Koopa::GetGravity()
{
	return gravity;
}
D3DXVECTOR2 Koopa::GetCollisionBox()
{
	return koopaState->GetCollisionBox();
}
void Koopa::SetHolder(CMario* h)
{
	holder = h;
}
CMario* Koopa::GetHolder()
{
	return holder;
}
void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	y += koopaState->GetCollisionBox().y;
	switch (state)
	{
	case KOOPA_STATE_WALKING:
		koopaState = new WalkingKoopa(this);
		break;
	case KOOPA_STATE_CROUCH:
		koopaState = new CrouchKoopa(this);
		break;	
	case KOOPA_STATE_SHELL_RUNNING:
		koopaState = new RunningShell(this);
		break;	
	}
	y -= koopaState->GetCollisionBox().y+5;

}