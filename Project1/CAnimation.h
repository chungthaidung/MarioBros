#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "CAnimationFrame.h"

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime=100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y,int scale=1,int flipx=1,int flipy=1, int alpha = 255);
	void Render(float x, float y, DWORD timestart, int totaltime, int scale=1,int flipx=1, int flipy = 1, int alpha = 255);
	void SetCurrentFrame(int a) { currentFrame = a; }
	int GetCurrentFrame() { return currentFrame; }
};

typedef CAnimation* LPANIMATION;

