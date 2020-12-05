#pragma once
#include "WalkingKoopa.h"
class FlyingKoopa :
    public WalkingKoopa
{
public:
	FlyingKoopa(Koopa* k);
	virtual void Update(DWORD dt);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
};
#define KOOPA_JUMP_FORCE	0.65f

