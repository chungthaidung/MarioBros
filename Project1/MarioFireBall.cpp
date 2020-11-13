#include "MarioFireBall.h"
#include "define.h"
#include "debug.h"
#include "CGame.h"
#include "debug.h"

MarioFireBall::MarioFireBall(CMario* p)
{
	mario = p;
}
void MarioFireBall::Render()
{
	int ani = MARIO_ANI_FIRE_BALL;
	switch (state)
	{
	case MARIO_FIRE_BALL_STATE_DAMAGED:
		ani = MARIO_ANI_FIRE_BALL_DAMAGED;
		
		break;
	case MARIO_FIRE_BALL_STATE:
		ani = MARIO_ANI_FIRE_BALL;
		break;
	}
	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	RenderBoundingBox();
}
void MarioFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_FIRE_BALL_BBOX_WIDTH ;
	b = y + MARIO_FIRE_BALL_BBOX_HEIGHT;
}
void MarioFireBall::Update(DWORD dt)
{
	vy += gravity * dt;
	CGameObject::Update(dt);
	vx = FIREBALL_SPEED*nx;
}
void MarioFireBall::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	coEResult.clear();
	CalcPotentialCollisions(coObjects, coEResult);
}
void MarioFireBall::FinalUpdate(DWORD dt)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	if (x > cx + SCREEN_WIDTH || x < cx)
	{
		active = false;
		isRemove = true;
	}
	// No collision occured, proceed normally
	if (coEResult.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) {
			vy = 0;
			vx = 0;
			gravity = 0;
			if (state != MARIO_FIRE_BALL_STATE_DAMAGED) {
				SetState(MARIO_FIRE_BALL_STATE_DAMAGED);
				damagedtime = GetTickCount();
			}
		}
		if (ny != 0) vy -= 0.5;
		//if (nx != 0) vx -= 0.5;

		//phuc hoi lai cho nay cho de thay
		//truong hop nay la vien dan cham goomba truoc, sang lan update sau goomba moi thay vien dan
		//neu remove tren kia thi no ko co animation nhi
		//oke, nhưng mà đặt debug xong là b thấy bug r hen, goomba thấy nó chạm viên đạn, nhưng sau 1 nùi lnhà nước update thì viên đạn mới thấy goomba, đúng logic là 2 đứa nó phải thấy nhau cùng lúc
		//nếu cùng lúc thì thứ tự nó phải liên tiếp mới cùng lúc đc nhỉ, thứ tự trong list ấy. đúng r....
		// với viên đạn thì mọi thứ vẫn ổn, nhưng qua động tác đạp quái sẽ có nhiều thứ để bàn á, đạp xong con quái trơ mặt ra chạy tiếp chẳng hạn =))))hm...
		//để tui demo cho xem nè.

	}
	State(dt);
	for (UINT i = 0; i < coEResult.size(); i++) {
		/*if (coEResult[i]->obj->GetObjectType() == OBJECT_TYPE_GOOMBA)
			DebugOut(L"Fireball collide with: %d\n", coEResult[i]->obj->GetObjectType());*/
		delete coEResult[i];
	}
}
void MarioFireBall::Reset(float mx,float my)
{
	if (mario != NULL) {
		SetState(MARIO_FIRE_BALL_STATE);
		gravity = FIREBALL_GRAVITY;
		vx = FIREBALL_SPEED * nx;
		x = mx;
		y = my;
		vy = 0;
		nx = mario->Getnx();
	}
}
int MarioFireBall::GetObjectType()
{
	return 20;
}

void MarioFireBall::State(DWORD dt)
{
	switch (state)
	{
	case MARIO_FIRE_BALL_STATE_DAMAGED:
		if (GetTickCount() - damagedtime >= 120) {
			active = false;

		}
		break;
	}
}