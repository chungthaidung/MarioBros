#pragma once
#include "WalkingKoopa.h"
class CrouchKoopa :
    public WalkingKoopa
{
public:
	CrouchKoopa(Koopa* k);
	virtual void Update(DWORD dt);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	//virtual void SetState(int state);
protected:
	DWORD respawntime;
};

