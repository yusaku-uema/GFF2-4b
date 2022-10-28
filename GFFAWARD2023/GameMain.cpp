#include"DxLib.h"
#include "GameMain.h"

GameMain::GameMain()
{

}


AbstractScene* GameMain ::Update()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
		return new GameMain;
	}
	return this;
}

void GameMain::Draw() const
{

}