#pragma once
#include "CGameObject.h"
class Effect :
    public CGameObject
{
public:
    Effect();
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual int GetObjectType();
protected: 
    DWORD time;
};

typedef Effect* LPEFFECT;