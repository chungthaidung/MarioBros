#include "PlayerLevel.h"
#include "CGameObject.h"
#include "GhostObject.h"
#include "debug.h"
PlayerLevel::PlayerLevel(CMario* mario)
{
	this->mario = mario;
}
void PlayerLevel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	mario->CGameObject::Update(dt);

	// Simple fall down
	mario->vy += MARIO_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (mario->state != MARIO_STATE_DIE)
		mario -> CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}*/

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		mario->x += mario->dx;
		mario->y += mario->dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		mario->FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		mario->x += min_tx * mario->dx + nx * 0.4f;
		mario->y += min_ty * mario->dy + ny * 0.4f;

		if (nx != 0) mario->vx = 0;
		if (ny != 0)
		{
			mario->vy = 0;
			if (ny < 0)
				mario->onGround = true;		
		} 

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<GhostObject*>(e->obj)) 
			{

				if (e->nx != 0) {
					mario->x += mario->dx;
				}
				if (e->ny > 0) {
					mario->y += mario->dy;
				}
				else {
					mario->vy = 0;
				}
			}
			else
			{
				if (e->nx != 0) {
					mario->vx = 0;
				}
				if (e->ny != 0)
				{
					mario->vy = 0;
				}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}

void PlayerLevel::SetState(int state)
{
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		mario->vx = MARIO_WALKING_SPEED;
		mario->nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		mario->vx = -MARIO_WALKING_SPEED;
		mario->nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
			mario->vy = -MARIO_JUMP_SPEED_Y;
		break;
	case MARIO_STATE_IDLE:
		mario->vx = 0;
		break;
	case MARIO_STATE_DIE:
		mario->vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		mario->vx = MARIO_WALKING_SPEED * 2;
		mario->nx = 1;
		break;
	
	}
}