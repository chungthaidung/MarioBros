#include "CPlaySceneKeyHandler.h"
#include "Mario.h"
#include "CPlayScene.h"
#include "define.h"
#include "WorldMario.h"
#include "WorldScene.h"
void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	if (scence->GetSceneType() == PLAY_SCENE) 
	{
		CMario* mario = ((CPlayScene*)scence)->GetPlayer();
		mario->OnKeyDown(KeyCode);
		switch (KeyCode)
		{
		case DIK_5:
			mario->SetPosition(7344.00, 1104.00);
			break;
		}
	}
	else if (scence->GetSceneType() == WORLD_MAP)
	{
		WorldMario* wmario= ((WorldScene*)scence)->GetPlayer();
		wmario->OnKeyDown(KeyCode);
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	if (scence->GetSceneType() == PLAY_SCENE)
	{
		CMario* mario = ((CPlayScene*)scence)->GetPlayer();
		mario->OnKeyUp(KeyCode);
	}
	else if (scence->GetSceneType() == WORLD_MAP)
	{
		WorldMario* wmario = ((WorldScene*)scence)->GetPlayer();
		wmario->OnKeyUp(KeyCode);
	}
}