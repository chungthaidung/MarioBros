#pragma once
#include "Effect.h"

#define SWITCH_BUTTON_ANI_DOWN  614

class SwitchButtonEff :
    public Effect
{
public:
    SwitchButtonEff();
    virtual void Update(DWORD dt);
    virtual void Render();
};

