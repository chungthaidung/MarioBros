#pragma once
#include "Effect.h"
#define TAIL_ATTACK_EFFECT_ANI  502
class TailAttackEf :
    public Effect
{
public:
    TailAttackEf();
    virtual void Update(DWORD dt);
    virtual void Render();
};

