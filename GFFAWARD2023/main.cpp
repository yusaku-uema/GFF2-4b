#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする
	SetMainWindowText("GFF");
	ChangeWindowMode(TRUE);
	SetWindowSize(1280, 720);
	
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0) {

	
		return 0;
	}
}
