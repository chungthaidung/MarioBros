#pragma once
#include "CScenceKeyHandler.h"
class CIntroSceneKeyHandler :
    public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CIntroSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};

};

