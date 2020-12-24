#pragma once
#include "Effect.h"

#define DEBRIS_ANI		606

#define LEFT_TOP 0
#define RIGHT_TOP 1
#define LEFT_BOTTOM 2
#define RIGHT_BOTTOM 3
class DebrisEff :
    public Effect
{
public:
    DebrisEff(int type);
    virtual void SetPosition(float x, float y);
    virtual void Update(DWORD dt);
    virtual void Render();
protected:
    int start_pos;
};

