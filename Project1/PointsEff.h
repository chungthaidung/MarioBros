#pragma once
#include "Effect.h"
class PointsEff :
    public Effect
{
public:
    PointsEff(int animation);
    virtual void Update(DWORD dt);
    virtual void Render();
protected:
    int ani;
    DWORD updatetime ;
};

