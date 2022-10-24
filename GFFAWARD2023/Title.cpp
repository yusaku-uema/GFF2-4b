#include"DxLib.h"
#include"Title.h"
#include "GameMain.h"

Title::Title()
{
	if ((g_title_image = LoadGraph("images/title1.png")) == -1);
}


AbstractScene* Title::Update()
{
	if(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
	{
		return new GameMain();
	}
	return this;
}

void Title::Draw() const
{
	DrawGraph(0, 0, g_title_image, FALSE);
}