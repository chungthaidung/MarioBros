#include "Font.h"

Font::Font(std::string dialog, D3DXVECTOR2 start_pos)
{
	c_char.clear();
	std::vector<char> convert(dialog.begin(), dialog.end());
	c_char = convert;
	this->start_pos = start_pos;
}

void Font::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void Font::Render()
{
	float pos_x = start_pos.x;
	float pos_y = start_pos.y;
	for (int i = 0; i < c_char.size(); i++)
	{
		int ani = int(c_char[i]) - 32;
		if (CAnimations::GetInstance()->Get(ani) == NULL)
			ani = LETTER_0;
		CAnimations::GetInstance()->Get(ani)->Render(pos_x, pos_y);
		switch (ani)
		{
		case 17:
			pos_x += 18;
			break;
		case 73:
			pos_x += 12;
			break;
		case 1:
			pos_x += 24;
			pos_y -= 6;
			break;
		default:
			pos_x += 24;
			break;
		}
	}
}

void Font::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;

}

void Font::SetDialog(std::string dialog)
{
	c_char.clear();
	std::vector<char> convert(dialog.begin(), dialog.end());
	c_char = convert;
}
