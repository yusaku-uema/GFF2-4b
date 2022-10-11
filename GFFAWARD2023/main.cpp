#include "DxLib.h"
#include"main.h"
#include"character.h"

int CharacterImages[16]; //少年のイメージ画像
int background1; //背景画像
int blockImages; //ブロック画像

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // タイトル
    SetMainWindowText("プロトタイプ版"); //ゲームタイトル
	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする
	ChangeWindowMode(TRUE);// ウィンドウモードで起動
	SetGraphMode(1280, 720, 0); //画面サイズ
    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	if (LoadImages() == -1)return -1; //画像読込み
	
	SetDrawScreen(DX_SCREEN_BACK); // 描画先画面を裏にする
    // ゲームループ
	while (ProcessMessage() == 0) {
        ClearDrawScreen();		// 画面の初期化

		DrawGraph(0, 100, background1, FALSE); //背景反映

		ScreenFlip();			// 裏画面の内容を表画面に反映

		
	}
		DxLib_End();	// DXライブラリ使用の終了処理

		return 0;
}


int LoadImages(void) { //画像読込み
	if (LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90,CharacterImages) == 1)return -1; //少年仮
	if((background1 = LoadGraph("images/background/street003_day.png")) == -1)return -1;// 背景
	if ((blockImages = LoadGraph("images/block/0115_s1.png")) == -1)return -1; //ブロック
	
}

int GetArrayImages(int type, int num) { //type,使いたい画像の要素数を指定することで、指定した画像が使える
	switch (type)
	{
	case Character: //少年
		if (0 <= num && num <= 16) {
			return CharacterImages[num];
		}
		else { return -1; }
		break;
	}
}