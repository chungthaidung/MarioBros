#include "Brick.h"
#include "debug.h"
Brick::Brick(CGameObject* obj, int type, float y) :QuestionBox(obj, y)
{
	state = type;
}

Brick::~Brick()
{
}

void Brick::Render()
{
	if (state!=BRICK_BROKEN){
		int ani = BRICK_ANI_REWARD;
		switch (state)
		{
		case BRICK_REWARD:
		case BRICK_BREAKABLE:
			ani = BRICK_ANI_REWARD;
			break;
		case BRICK_EMPTY:
			ani = BRICK_ANI_EMPTY;
			break;
		}
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
		RenderBoundingBox();
	}
	else
	{
		broken->Render();
	}
	
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_WIDTH;
}

void Brick::Update(DWORD dt)
{
	if (state != BRICK_BROKEN){
		vy += gravity * dt;

		CGameObject::Update(dt);
	}
	else
	{
		broken->Update(dt);
	}
	
}

void Brick::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state != BRICK_BROKEN) {
		CalcPotentialCollisions(coObjects, coEResult);
	}
	
}

void Brick::FinalUpdate(DWORD dt)
{
	if (state == BRICK_BROKEN && GetTickCount() - time> 100) isRemove = true;
	if (state == BRICK_EMPTY || state == BRICK_BROKEN) return;

	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	if (coEResult.size() == 0)
	{
		//x += dx;
		y += dy;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	}

	//
	// Collision logic with other objects
	//
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
		{
			 if (state == BRICK_BREAKABLE)
			{
				if (e->ny < 0)
				{
					SetState(BRICK_BROKEN);
				}
			}
			
		}
		else if ((e->obj->GetObjectType() == OBJECT_TYPE_KOOPA && e->obj->GetState() == KOOPA_STATE_SHELL_RUNNING) || (e->obj->GetObjectType() == OBJECT_TYPE_TAIL))
		{
			if (state == BRICK_REWARD) 
			{
				if (e->nx != 0)
				{
					SetState(BRICK_BOUNC);
				}
			}
			else if (state == BRICK_BREAKABLE)
			{
				if (e->nx != 0 )
				{
					SetState(BRICK_BROKEN);
				}
			}
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete coEResult[i];
	coEResult.clear();
	if(state == BRICK_BOUNC)
	{
		if (y < y_start - 40)
		{
			vy = 0;
			y = y_start - 40;
		}
		else if (y == y_start - 40)
		{
			SetState(BRICK_EMPTY);
		}
	}
}

void Brick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_BOUNC:
		vy = -0.5;
		break;
	case BRICK_EMPTY:
		vy = 0;
		y = y_start;
		gravity = 0;
		break;
	case BRICK_BREAKABLE:
		break;
	case BRICK_BROKEN:
		time = GetTickCount();
		broken = new BrokenBrick(this);
		//isRemove = true;
		//DebugOut(L"aaaa \n");
		break;
	}
}

int Brick::GetObjectType()
{
	return OBJECT_TYPE_BRICK;
}

void Brick::SetWidthHeight(int w, int h)
{
	width = BRICK_BBOX_WIDTH;
	height = BRICK_BBOX_HEIGHT;
}
