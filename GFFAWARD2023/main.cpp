#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // タイトル
    SetMainWindowText("GFF");
	ChangeWindowMode(TRUE);// ウィンドウモードで起動
	SetWindowSize(1280, 720); //画面サイズ
    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	
	SetDrawScreen(DX_SCREEN_BACK);// 描画先画面を裏にする
    // ゲームループ
	while (ProcessMessage() == 0) {
        ClearDrawScreen();		// 画面の初期化

		ScreenFlip();			// 裏画面の内容を表画面に反映

		DxLib_End();	// DXライブラリ使用の終了処理

		return 0;
	}

}
