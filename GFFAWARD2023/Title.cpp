#include"DxLib.h"
#include"Title.h"
#include "GameMain.h"

Title::Title()
{
	if ((img = LoadGraph("images/Title1.png")) == -1);
}


AbstractScene* Title::Update()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
		return new GameMain;
	}
	return this;
}

void Title::Draw() const
{
	DrawGraph(0, 0, img, FALSE);
	DrawString(640, 360, "AÇ≈ÉQÅ[ÉÄ", GetColor(255, 0, 0));
}