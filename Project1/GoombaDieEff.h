#pragma once
#include "Effect.h"
class GoombaDieEff : //enemy die effect
    public Effect
{
public:
    GoombaDieEff(int animation);
    GoombaDieEff(int animation,float vy,int ny);
    virtual void Update(DWORD dt);
    virtual void Render();
protected:
    int ani;
};

