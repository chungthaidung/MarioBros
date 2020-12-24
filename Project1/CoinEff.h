#pragma once
#include "Effect.h"
#define COIN_EFFECT_ANI 503
class CoinEff :
    public Effect
{
public:
    CoinEff();
    ~CoinEff();
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void SetPosition(float x,float y);
protected:
    float y_start;
};

