#pragma once
#include "Effect.h"
#define ENEMY_DAMAGED_EFFECT_ANI    507
class EnemyDamagedEff :
    public Effect
{
public:
    EnemyDamagedEff();
    virtual void Update(DWORD dt);
    virtual void Render();
};

