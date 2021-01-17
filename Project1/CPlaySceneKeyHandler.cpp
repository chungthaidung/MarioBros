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
	}
	else if (scence->GetSceneType() == WORLD_MAP)
	{
		WorldMario* wmario= ((WorldScene*)scence)->GetPlayer();
		wmario->OnKeyDown(KeyCode);
	}
	
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	
	//CGame* game = CGame::GetInstance();
	

	//switch (mario->GetState())
	//{
	//case MARIO_STATE_DIE:
	//	return;
	//	//moving mario
	//case MARIO_STATE_IDLE:
	//	if (game->IsKeyDown(DIK_RIGHT))
	//		mario->SetState(MARIO_STATE_WALKING_RIGHT);
	//	if (game->IsKeyDown(DIK_LEFT))
	//		mario->SetState(MARIO_STATE_WALKING_LEFT);
	//	break;
	//case MARIO_STATE_WALKING_RIGHT:
	//	if (game->IsKeyDown(DIK_A))
	//		mario->SetState(MARIO_STATE_RUNNING_RIGHT);
	//	break;
	//case MARIO_STATE_WALKING_LEFT:
	//	if (game->IsKeyDown(DIK_A))
	//		mario->SetState(MARIO_STATE_RUNNING_LEFT);
	//	break;
	//	// jumping mario
	//case MARIO_STATE_JUMP:
	//	if (mario->onGround == true)
	//		mario->SetState(MARIO_STATE_IDLE);
	//	break;

	//}
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