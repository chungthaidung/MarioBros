#include "Venus.h"
#include "Mario.h"
#include "CPlayScene.h"
#include "debug.h"
#include "EnemyDamagedEff.h"
Venus::Venus(int t, int ny, float start_y)
{
	type = t;
	isEnemy = true;
	this->ny = ny;
	y_start = start_y;
	SetState(VENUS_STATE_UP);
	head = VENUS_HEAD_UP;
	fireball = new VenusFireBall(this);
	renderOrder = 1;
}

void Venus::Update(DWORD dt)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	if (mario->GetPosition().x > x)
		nx = 1;
	else nx = -1;
	if (mario->GetPosition().y > y)
		head = VENUS_HEAD_DOWN;
	else head = VENUS_HEAD_UP;
	if (y > y_start && state == VENUS_STATE_DOWN)
	{
		y = y_start;
		if (mario->GetPosition().x > x - 72 && mario->GetPosition().x < x + VENUS_BBOX_WIDTH + 72)
			SetState(VENUS_STATE_DOWN);
		else
			SetState(VENUS_STATE_UP);
	}
	else if (y < y_start - 102 && state == VENUS_STATE_UP && type==GREEN_TYPE)
	{
		y = y_start - 102;
		SetState(VENUS_STATE_IDLE);
	}
	else if (y < y_start - 126 && state == VENUS_STATE_UP && type == RED_TYPE)
	{
		y = y_start - 126;
		SetState(VENUS_STATE_IDLE);
	}
	else if (state == VENUS_STATE_IDLE && GetTickCount() - staytime > 500)
	{
		if (GetTickCount() - staytime > 1000)
		{
			SetState(VENUS_STATE_DOWN);
		}
		else if (GetTickCount() - staytime > 500 && fireball->GetActive()==false) 
		{
			Attack();
		}
	}
	CGameObject::Update(dt);
}

void Venus::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CalcPotentialCollisions(coObjects, coEResult);
}

void Venus::FinalUpdate(DWORD dt)
{
	y += dy;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEventsResult.clear();
	
	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;
	FilterCollision(coEResult, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if ((e->obj->GetObjectType() == OBJECT_TYPE_TAIL || e->obj->GetObjectType() == OBJECT_TYPE_FIREBALL) && e->nx != 0)
		{
			EnemyDamagedEff* eff = new EnemyDamagedEff();
			eff->SetPosition(x, y);
			CGame::GetInstance()->GetCurrentScene()->AddEffect(eff);
			fireball->canDelete = true;
			isRemove = true;
		}
	}
	for (UINT i = 0; i < coEResult.size(); i++) delete  coEResult[i];
	coEResult.clear();
}

void Venus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_UP:
		vy = -0.05f;
		break;
	case VENUS_STATE_DOWN:
		vy = 0.05f;
		break;
	case VENUS_STATE_IDLE:
		vy = 0.0f;
		staytime = GetTickCount();
		break;
	}
}

void Venus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + VENUS_BBOX_WIDTH;
	bottom = y + VENUS_BBOX_HEIGHT;
}

void Venus::Render()
{
	int ani = GREEN_VENUS_ANI_HEAD_UP;
	int f = -1;//sprite bi nguoc
	if (type == GREEN_TYPE) {
		switch (head)
		{
		case VENUS_HEAD_UP:
			if (state == VENUS_STATE_IDLE)
				ani = GREEN_VENUS_ANI_HEAD_UP_IDLE;
			else
				ani =GREEN_VENUS_ANI_HEAD_UP;
			break;
		case VENUS_HEAD_DOWN:
			if (state == VENUS_STATE_IDLE)
				ani = GREEN_VENUS_ANI_HEAD_DOWN_IDLE;
			else
				ani = GREEN_VENUS_ANI_HEAD_DOWN;
			break;
		}
	}
	else if (type == RED_TYPE)
	{
		switch (head)
		{
		case VENUS_HEAD_UP:
			if (state == VENUS_STATE_IDLE)
				ani = RED_VENUS_ANI_HEAD_UP_IDLE;
			else
				ani = RED_VENUS_ANI_HEAD_UP;
			break;
		case VENUS_HEAD_DOWN:
			if (state == VENUS_STATE_IDLE)
				ani = RED_VENUS_ANI_HEAD_DOWN_IDLE;
			else
				ani = RED_VENUS_ANI_HEAD_DOWN;
			break;
		}
	}
	float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
	float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
	CAnimations::GetInstance()->Get(ani)->Render(x-cx, y-cy, 1, nx*f, ny);
	RenderBoundingBox();
}

int Venus::GetObjectType()
{
	return OBJECT_TYPE_VENUS;
}

bool Venus::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
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

void Venus::Attack()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = scene->GetPlayer();
	float mx , my ,x_s,y_s, distance;
	x_s = x - VENUS_FIRE_BALL_BBOX_WIDTH;
	y_s = y + VENUS_FIRE_BALL_BBOX_HEIGHT;
	if (nx == 1)
	{
		x_s = x + GetCollisionBox().x ;
	}
	if (head == VENUS_HEAD_UP)
	{
		y_s = y + VENUS_FIRE_BALL_BBOX_HEIGHT-15;

	}
//	DebugOut(L"mario x: %f, mario y: %f || venus x: %f, venus y: %f \n", mario->GetPosition().x, mario->GetPosition().y, x, y);
	distance = (mario->GetPosition().y - y_s) * (mario->GetPosition().y - y_s) + (mario->GetPosition().x - x_s) * (mario->GetPosition().x - x_s);
	mx = abs(mario->GetPosition().x - x_s) / sqrt(distance);
	my = abs(mario->GetPosition().y - y_s) / sqrt(distance);
	mx = min(sin(PI * 7/18), max(mx, sin(PI * 2 / 9))); // trong khoang 40 ~ 70 do
	my = max(cos(PI * 7 / 18), min(my, cos(PI * 2 / 9))); // trong khoang 40 ~ 70 do
	/*if (mx < sin(PI * 2 / 9) || mx > sin(PI * 5 / 12))
	{
		mx = sin(PI * 2 / 9);
	}
	if (my > cos(PI * 2 / 9)) my = cos(PI * 2 / 9);*/
//	DebugOut(L"mx: %f, my: %f, distance: %f \n", mx, my, sqrt(distance));
	fireball->SetActive(true);
	CGame::GetInstance()->GetCurrentScene()->SpawnObjectWithoutGrid(fireball);
	fireball->Reset(x_s, y_s, mx, my);
}

int Venus::GetType()
{
	return type;
}

int Venus::GetHead()
{
	return head;
}

D3DXVECTOR2 Venus::GetCollisionBox()
{
	return D3DXVECTOR2(VENUS_BBOX_WIDTH, VENUS_BBOX_HEIGHT);
}
