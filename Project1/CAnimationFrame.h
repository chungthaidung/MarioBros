#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "CSprite.h"
// 	Sprite animation
using namespace std;
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame* LPANIMATION_FRAME;
