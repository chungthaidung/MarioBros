#include "Brick.h"
#include "debug.h"
#include "CGame.h"
#include "CoinEff.h"
#include "SuperLeaf.h"
#include "Coin.h"
#include "SwitchButton.h"
#include "DebrisEff.h"
Brick::Brick(int obj_type, int type, float y) :QuestionBox(obj_type, y)
{
	state = type;
	QuestionBox::SetReward(obj_type);
}

Brick::~Brick()
{
}

void Brick::Render()
{
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
	case BRICK_COIN:
		ani = COIN_ANI;
		break;
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy);
	RenderBoundingBox();
}

void Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_WIDTH;
}

bool Brick::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
	if (obj->GetObjectType() == OBJECT_TYPE_MARIO)
	{
		CMario* mario = dynamic_cast<CMario*>(obj);
		if (mario->GetUntouchable() == true) return true;
	}
	return false;
}

void Brick::Update(DWORD dt)
{
	CGameObject::Update(dt);
	
}

void Brick::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);

}

void Brick::FinalUpdate(DWORD dt)
{
	if (state == BRICK_EMPTY || state == BRICK_BROKEN) return;

	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	Effect* eff = NULL;

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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->GetObjectType() == OBJECT_TYPE_MARIO)
			{
				CMario* mario = dynamic_cast<CMario*>(e->obj);
				if (mario->GetLevel() != MARIO_LEVEL_SMALL && state == BRICK_BREAKABLE)
				{
					if (e->ny < 0)
					{
						for (int i = 0; i < 4; i++)
						{
							DebrisEff* eff = new DebrisEff(i);
							eff->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
						}
						SetState(BRICK_BROKEN);
						
					}
				}
				else if (state == BRICK_REWARD)
				{
					if (e->nx < 0)
					{
						SetState(BRICK_BOUNC);
					}
				}
				else if (state == BRICK_COIN)
				{
					CGame::GetInstance()->SetPoints(100);
					isRemove = true;
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
					if (e->nx != 0)
					{
						for (int i = 0; i < 4; i++)
						{
							DebrisEff* eff = new DebrisEff(i);
							eff->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
						}
						SetState(BRICK_BROKEN);
						
					}
				}
			}
		}
	}

	//
	// Collision logic with other objects
	//
	
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
			if (reward->GetObjectType() != OBJECT_TYPE_COIN) {
				CGame::GetInstance()->GetCurrentScene()->SpawnObject(reward);
			}
			else
			{
				eff = new CoinEff();
				CGame::GetInstance()->SetPoints(100);
				eff->SetPosition(x, y);
				CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
			}
		}
	}
	RewardChecking();

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
		reward->SetPosition(x, y);

		//if (reward->GetObjectType() == OBJECT_TYPE_SUPER_LEAF)
		//{
		//	SuperLeaf* leaf = dynamic_cast<SuperLeaf*>(reward);
		//	//leaf->SetXStart(x);

		//} else
		 if (reward->GetObjectType() == OBJECT_TYPE_SWITCH_BUTTON)
		{
			reward->SetPosition(x, y-48);
		}
		break;
	case BRICK_BREAKABLE:
		break;
	case BRICK_BROKEN:
		isRemove = true;
		break;
	case BRICK_COIN:
		/*coin = new Coin();
		coin->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->SpawnObject(coin);*/
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

void Brick::SpawnCoin()
{
	SetState(BRICK_COIN);
}

void Brick::DespawnCoin()
{
	SetState(BRICK_BREAKABLE);
}
