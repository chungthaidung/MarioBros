#include "CIntroSceneKeyHandler.h"
#include "CPlaySceneKeyHandler.h"
#include "Mario.h"
#include "CPlayScene.h"
#include "define.h"
#include "WorldMario.h"
#include "WorldScene.h"
void CIntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_W:
		scence->SetisUnload(true);
		break;
	}
}

void CIntroSceneKeyHandler::KeyState(BYTE* states)
{
}
void CIntroSceneKeyHandler::OnKeyUp(int KeyCode)
{
}