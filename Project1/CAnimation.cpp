#include "CAnimation.h"
#include <d3dx9.h>

#include "CSprites.h"
#include "CGame.h"
#include "Utils.h"
#include "debug.h"
#include <string>

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;
	DebugOut(ToLPCWSTR("[INFO] Sprite ID: " + std::to_string(spriteId) + "\n"));
	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y,int scale,int flipx, int flipy , int alpha)
{
	DWORD now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	frames[currentFrame]->GetSprite()->Draw(x, y,scale,flipx,flipy, alpha);
}

void CAnimation::Render(float x, float y, DWORD timestart, int totaltime, int scale, int flipx, int flipy, int alpha)
{
	DWORD now = GetTickCount64();
	int c_frame = (now - timestart) * frames.size() / totaltime;
	if (c_frame < 0) c_frame = 0;
	if (c_frame > frames.size())c_frame = frames.size();
	frames[c_frame]->GetSprite()->Draw(x, y, scale, flipx,flipy, alpha);
}

