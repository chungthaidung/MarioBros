#pragma once
#include "Effect.h"
#define FIREBALL_DAMAGED_EFFECT_ANI 501
class FireBallEf :
    public Effect
{
public:
    FireBallEf();
    virtual void Update(DWORD dt);
    virtual void Render();
};

