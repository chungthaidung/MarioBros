#include "Opening.h"
#include "define.h"
#include "CGame.h"
int Opening::GetObjectType()
{
    return OBJECT_TYPE_OPENING;
}

bool Opening::GetThrough(CGameObject* obj, D3DXVECTOR2 direction)
{
    return true;
}

Opening::Opening()
{
    vx = 0;
    vy = -0.2;
}

void Opening::Update(DWORD dt)
{
    if (y + SCREEN_HEIGHT < SCREEN_HEIGHT/7)
    {
        vy = 0;
    }
    CGameObject::Update(dt);
}

void Opening::CollisionUpdate(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CalcPotentialCollisions(coObjects, coEResult);
}

void Opening::FinalUpdate(DWORD dt)
{
    x += dx;
    y += dy;
}

void Opening::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x;
    top = y;
    right = x+SCREEN_WIDTH;
    bottom = y+ SCREEN_HEIGHT;
}

void Opening::Render()
{
    float cx = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.x;
    float cy = CGame::GetInstance()->GetCurrentScene()->GetCamera()->position.y;
    CAnimations::GetInstance()->Get(OPENING_ANI)->Render(x-cx, y-cy);
}
