#include"DxLib.h"
#include"End.h"
#include "GameMain.h"

End::End()
{
	if ((g_end_image = LoadGraph("images/title.png")) == -1);
}


AbstractScene* End::Update()
{
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
	{
		return new GameMain();
	}
	return this;
}

void End::Draw() const
{
	DrawGraph(0, 0, g_end_image, FALSE);
