#include"DxLib.h"
#include"Title.h"


Title::Title()
{
	if ((g_title_image = LoadGraph("images/title.png")) == -1);
}


AbstractScene* Title::Update()
{

}

void Title::Draw() const
{

}