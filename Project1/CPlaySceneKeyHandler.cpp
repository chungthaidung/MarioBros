#include "CPlaySceneKeyHandler.h"
#include "Mario.h"
#include "CPlayScene.h"

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	/*CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->Reset();
		break;
	}*/
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	//CGame* game = CGame::GetInstance();
	//CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	//// disable control key when Mario die 
	//if (mario->GetState() == MARIO_STATE_DIE) return;
	//if (game->IsKeyDown(DIK_RIGHT))
	//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//else if (game->IsKeyDown(DIK_LEFT))
	//	mario->SetState(MARIO_STATE_WALKING_LEFT);
	//else
	//	mario->SetState(MARIO_STATE_IDLE);
}