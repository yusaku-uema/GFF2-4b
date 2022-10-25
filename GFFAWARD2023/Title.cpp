#include"DxLib.h"
#include"Title.h"
#include "GameMain.h"

Title::Title()
{
	if ((g_title_image = LoadGraph("images/title1.png")) == -1);
}


AbstractScene* Title::Update()
{
	g_drawingtime++;
	if (g_drawingtime > 60) {
		g_drawingtime = 0;
	}

	if(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
	{
		return new GameMain();
	}
	return this;
}

void Title::Draw() const
{
	DrawGraph(0, 0, g_title_image, FALSE);
	SetFontSize(64);
	if (g_drawingtime < 30)
	{
		DrawString(150, 455, "---Aボタンでゲームスタート---", GetColor(255, 255, 255));
	}

}