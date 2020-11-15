#include "FireMario.h"
#include "CGame.h"
#include "debug.h"
FireMario::FireMario(CMario* mario) :PlayerLevel(mario)
{
	collisionbox.x = MARIO_FIRE_BBOX_WIDTH;
	collisionbox.y = MARIO_FIRE_BBOX_HEIGHT;

	for (int i = 0; i < 2; i++)
	{
		MarioFireBall* ball = new MarioFireBall(mario);
		ball->SetActive(false);
		fireballs.push_back(ball);
	}
}

void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	mario->GetPosition(left, top);
	right = left + collisionbox.x;
	bottom = top + collisionbox.y;
}
void FireMario::Render()
{
	int alpha = 255;
	int f = 1;
	int ani = MARIO_ANI_FIRE_IDLE;
	if (mario->GetState() == MARIO_STATE_CROUCH)
	{
		ani = MARIO_ANI_FIRE_CROUCH;
		CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx * f,1, alpha);
		mario->RenderBoundingBox();
	}
	else if (mario->AttackState == MARIO_STATE_ATTACK_START)
	{
		ani = MARIO_ANI_FIRE_THROW;
		CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y,attacktime,250, 1, mario->nx * f,1, alpha);
		mario->RenderBoundingBox();

	}
	else if (mario->JumpState != MARIO_STATE_JUMP_IDLE)
	{
		switch (mario->JumpState)
		{
		case MARIO_STATE_JUMP:
		case MARIO_STATE_HIGH_JUMP:
			ani = MARIO_ANI_FIRE_JUMP;
			break;
		case MARIO_STATE_FALL:
			ani = MARIO_ANI_FIRE_FALL;
			break;
		case MARIO_STATE_SUPER_FALL:
		case MARIO_STATE_SUPER_JUMP:
			ani = MARIO_ANI_FIRE_SUPER_JUMP;
			break;
		}
		CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx * f,1, alpha);
		mario->RenderBoundingBox();
	}
	else {
		switch (mario->GetState())
		{
		case MARIO_STATE_IDLE:
			ani = MARIO_ANI_FIRE_IDLE;
			break;
		case MARIO_STATE_WALKING:
			ani = MARIO_ANI_FIRE_WALKING;
			break;
		case MARIO_STATE_RUNNING:
			ani = MARIO_ANI_FIRE_RUNNING;
			break;
		case MARIO_STATE_JUMP:
			ani = MARIO_ANI_FIRE_JUMP;
			break;
		case MARIO_STATE_SKID:
			ani = MARIO_ANI_FIRE_SKID;
			f = -1;
			break;

		}
		CAnimations::GetInstance()->Get(ani)->Render(mario->x, mario->y, 1, mario->nx * f,1, alpha);
		mario->RenderBoundingBox();
	}

	

}
void FireMario::AttackState(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	if (keyboard->IsKeyDown(DIK_Z) && mario->AttackState != MARIO_STATE_ATTACK_START)
	{
		if (IsActive() == false)
		{
			mario->AttackState = MARIO_STATE_ATTACK_START;
			attacktime = GetTickCount();
		}
		else mario->AttackState = MARIO_STATE_ATTACK_END;
	}
	switch (mario->AttackState)
	{
	case MARIO_STATE_ATTACK_START:
		DWORD now = GetTickCount();
		if (now - attacktime < 250)
		{
			if (now - attacktime > 100 && !IsActive()) {
				AttackStart();
			}
		}
		else mario->AttackState = MARIO_STATE_ATTACK_END;
		break;
	}
	//DebugOut(L"Is Active %d ball num %d \n", fireballs.at(ballnumber)->GetActive(),ballnumber);
}
void FireMario::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_A:
		if (IsActive() == false)
		{
			mario->AttackState = MARIO_STATE_ATTACK_START;
			attacktime = GetTickCount();
		}
		else mario->AttackState = MARIO_STATE_ATTACK_END;
		break;
	}
}
int FireMario::GetPlayerLevel()
{
	return 4;
}
bool FireMario::IsActive()
{

	for (int i = 0; i < 2; i++)
	{
		if (fireballs.at(i)->GetActive() == false)
		{
			return false;
		}
	}
	return true;
}
void FireMario::AttackStart()
{
	for (int i = 0; i < 2; i++)
	{
		if (fireballs.at(i)->GetActive() == false)
		{
			fireballs.at(i)->SetActive(true);
			CGame::GetInstance()->GetCurrentScene()->SpawnObject(fireballs.at(i));
			if (mario->nx > 0) fireballs.at(i)->Reset(mario->x + collisionbox.x, mario->y+collisionbox.y*1/3);
			else fireballs.at(i)->Reset(mario->x - MARIO_FIRE_BALL_BBOX_WIDTH, mario->y+ collisionbox.y * 1 / 3);
			mario->AttackState = MARIO_STATE_ATTACK_END;
			break;
		}
	}
}
