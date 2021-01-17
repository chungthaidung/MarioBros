#include "WorldMario.h"
#include "debug.h"
#include "CGame.h"
#include "CheckPoint.h"
WorldMario::WorldMario()
{
	vx = 0; 
	vy = 0;
}

void WorldMario::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void WorldMario::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void WorldMario::FinalUpdate(DWORD dt)
{
	CGame* keyboard = CGame::GetInstance();
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
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
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)  vx =0;
		if (ny != 0)
		{
			vy = 0;
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_CHECKPOINT )
			{
				CheckPoint* checkpoint = dynamic_cast<CheckPoint*>(e->obj);
				if (e->ny != 0) {
					if (e->ny > 0) vy = -0.01;
					if (e->ny < 0) vy = 0.01;
				}
				if (e->nx != 0) {
					if (e->nx > 0) vx = -0.01;
					if (e->nx < 0) vx = 0.01;
				}
				if (keyboard->IsKeyDown(DIK_W) && checkpoint->CanTele() == true)
					CGame::GetInstance()->SwitchScene(checkpoint->GetSceneID());
			}
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
}

void WorldMario::Render()
{
	int ani = MARIO_WORLD_ANI_SMALL;
	switch (level_p)
	{
	case MARIO_LEVEL_SMALL:
		ani = MARIO_WORLD_ANI_SMALL;
		break;
	case MARIO_LEVEL_BIG:
		ani = MARIO_WORLD_ANI_BIG;
		break;
	case MARIO_LEVEL_RACOON:
		ani = MARIO_WORLD_ANI_RACOON;
		break;
	case MARIO_LEVEL_FIRE:
		ani = MARIO_WORLD_ANI_FIRE;
		break;
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	int alpha = 255;
	CAnimations::GetInstance()->Get(ani)->Render(x - cx, y - cy, 1, nx , 1, alpha);
	RenderBoundingBox();
}

void WorldMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_WORLD_BBOX_WIDTH;
	bottom = y + MARIO_WORLD_BBOX_HEIGHT;
}

int WorldMario::GetObjectType()
{
	return OBJECT_TYPE_WORLD_MARIO;
}

void WorldMario::SetLevel(int level)
{
	level_p = level;
}

void WorldMario::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_RIGHT:
		if (vx != 0) x += 1;
		vx = 0.3;
		break;
	case DIK_LEFT:
		if (vx != 0) x -= 1;
		vx = -0.3;
		break;
	case DIK_UP:
		if (vy != 0) y -= 1;
		vy = -0.3;
		break;
	case DIK_DOWN:
		if (vy != 0) y += 1;
		vy = 0.3;
		break;
	default:
		break;
	}
}

void WorldMario::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	default:
		break;
	}
}
