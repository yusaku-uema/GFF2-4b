#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���
	SetMainWindowText("GFF");
	ChangeWindowMode(TRUE);
	SetWindowSize(1280, 720);
	
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0) {

	
		return 0;
	}
}
