#pragma once
#include "Effect.h"
class MarioDieEff :
    public Effect
{
public:
    MarioDieEff(D3DXVECTOR2 pos);
    virtual void Update(DWORD dt);
    virtual void Render();
protected:
    float gravity;
    DWORD time;
    bool jump = true;
};

