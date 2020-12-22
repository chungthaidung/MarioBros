#pragma once
#include "Effect.h"
class EndGameRewardEff :
    public Effect
{
public:
    EndGameRewardEff(int ani);
    virtual void Update(DWORD dt);
    virtual void Render();
protected:
    int ani;
};

