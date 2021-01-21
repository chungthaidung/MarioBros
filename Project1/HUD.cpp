#include "HUD.h"
#include "debug.h"
#include "CGame.h"
HUD::HUD()
{
	pmeter = new PMeterHUD();
	hudposition.x = HUD_POSITION_X;
	hudposition.y = HUD_POSITION_Y;
	cardposition.x = CARD_POSITION_X;
	cardposition.y = CARD_POSITION_Y;
	string count = std::to_string(CGame::GetInstance()->GetCurrentScene()->GetPlayTime()/1000);
	std::string new_count = std::string(3 - count.length(), '0') + count;
	time = new Font(new_count, D3DXVECTOR2(382, 74));
	count = std::to_string(CGame::GetInstance()->GetMarioLife());
	if (CGame::GetInstance()->GetMarioLife() <= 0)
		count = std::to_string(0);
	life = new Font(count, D3DXVECTOR2(121, 74));
	count = std::to_string(CGame::GetInstance()->GetStageClear());
	stageclear = new Font(count, D3DXVECTOR2(408,48));
	count = std::to_string(CGame::GetInstance()->GetPoints());
	std::string new_points = std::string(7 - count.length(), '0') + count;
	points = new Font(new_points, D3DXVECTOR2(171, 74));
}

void HUD::Update(DWORD dt)
{
	//if (!target->endgame_reward.empty())DebugOut(L"[INFO] Endgame reward size: %d\n", target->endgame_reward.size());
	pmeter->Update(dt);
	string count = std::to_string(CGame::GetInstance()->GetCurrentScene()->GetPlayTime() / 1000);
	std::string new_count = std::string(3 - count.length(), '0') + count;
	time = new Font(new_count, D3DXVECTOR2(382, 74));
	count = std::to_string(CGame::GetInstance()->GetMarioLife());
	if (CGame::GetInstance()->GetMarioLife() <= 0)
		count = std::to_string(0);
	life = new Font(count, D3DXVECTOR2(121, 74));
	count = std::to_string(CGame::GetInstance()->GetStageClear());
	stageclear = new Font(count, D3DXVECTOR2(408, 50));
	count = std::to_string(CGame::GetInstance()->GetPoints());
	std::string new_points = std::string(7 - count.length(), '0') + count;
	points = new Font(new_points, D3DXVECTOR2(171, 74));
}

void HUD::Render()
{
	CAnimations::GetInstance()->Get(HUD_ANI)->Render(hudposition.x, hudposition.y);
	for (int i = 0; i < 3; i++)
	{
		int cardani = CARD_ANI;
		if (!target->endgame_reward.empty() && target->endgame_reward[i] != NULL) // &&target->endgame_reward.size()<i
		{
			if (target->endgame_reward[i] == MUSHROOM)
				cardani = MUSHROOM_CARD_ANI;
			else if (target->endgame_reward[i] == FLOWER)
				cardani = FLOWER_CARD_ANI;
			else if (target->endgame_reward[i] == STAR)
				cardani = STAR_CARD_ANI;
		}
		CAnimations::GetInstance()->Get(cardani)->Render(cardposition.x+81*i, cardposition.y);
	}
	pmeter->Render();
	time->Render();
	life->Render();
	stageclear->Render();
	points->Render();
}

void HUD::SetTarget(CMario* mario)
{
	if (mario != NULL)
	{
		target = mario;
		pmeter->SetTarget(mario);
	}
}

CMario* HUD::GetTarget()
{
	return target;
}
