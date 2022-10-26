#include"DxLib.h"
#include"Title.h"
#include "GameMain.h"

Title::Title()
{

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
	DrawString(0, 0, "AÇ≈ÉQÅ[ÉÄ", GetColor(255, 0, 0));
}