#pragma once
#include "Effect.h"
#define MUSHROOM	1
#define FLOWER	2
#define STAR	3
class Card :
    public Effect
{
public:
    Card(int type,D3DXVECTOR2 pos);
    virtual void Update(DWORD dt);
    virtual void Render();
};

