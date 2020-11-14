#pragma once
#include "WalkingKoopa.h"
class RunningShell :
    public WalkingKoopa
{
public:
	RunningShell(Koopa* k);
	virtual void Update(DWORD dt);
	virtual void FinalUpdate(DWORD dt);
	virtual void Render();
	//virtual void SetState(int state);

};

