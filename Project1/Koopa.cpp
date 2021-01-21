#include "Koopa.h"
#include "define.h"
#include "Mario.h"
#include "MarioTail.h"
#include "debug.h"
#include "WalkingKoopa.h"
#include "CrouchKoopa.h"
#include "RunningShell.h"
#include "FlyingKoopa.h"
#include "CCollisionEvent.h"
#include "GoombaDieEff.h"
#include "CGame.h"
Koopa::Koopa(int t)
{
	koopaState = new WalkingKoopa(this);
	type = t;
	isEnemy = true;
	//state = KOOPA_STATE_WALKING;
}
Koopa::~Koopa()
{
}
void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + koopaState->GetCollisionBox().x;
	bottom = y + koopaState->GetCollisionBox().y;

}
bool Koopa::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_SUPER_MUSHROOM || obj->GetObjectType() == OBJECT_TYPE_SUPER_LEAF || obj->GetObjectType() == OBJECT_TYPE_VENUS_FIREBALL)
		return true;
	if (obj->GetObjectType() == OBJECT_TYPE_GHOST && (direction.y > 0 || direction.x != 0))
		return true;
	if (obj->GetObjectType() == OBJECT_TYPE_COIN)
		return true;
	if (obj->GetState() == BRICK_COIN && obj->GetObjectType() == OBJECT_TYPE_BRICK) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_END_GAME_REWARD) return true;
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
	{
		CMario* mario = dynamic_cast<CMario*>(obj);
		if (mario->GetUntouchable() == true) return true; //khong xet va cham voi mario trong trang thai untouchable
	}
	return false;
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
	if (y > CGame::GetInstance()->GetCurrentScene()->GetBoundary().bottom) isRemove = true;
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
void Koopa::SetType(int type)
{
	this->type = type;
}
int Koopa::GetType()
{
	return type;
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
	case KOOPA_STATE_FLYING:
		koopaState = new FlyingKoopa(this);
		break;	
	case KOOPA_STATE_DIE:
		isRemove = true;
		int ani = KOOPA_ANI_CROUCH;
		if(type==RED_KOOPA)
			ani = RED_KOOPA_ANI_CROUCH;
		Effect* eff = new GoombaDieEff(ani);
		eff->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
		break;
	}
	y -= koopaState->GetCollisionBox().y+5;

}
