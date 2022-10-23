#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

/***********************************************
 * プログラム開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("ゲーム");  //タイトルを設定

    SetGraphMode(1280, 720, 16);
    ChangeWindowMode(TRUE);		               // ウィンドウモードで起動

    if (DxLib_Init() == -1) return -1;	   // DXライブラリの初期化処理
    SceneManager* sceneMng;
    SetDrawScreen(DX_SCREEN_BACK);	           // 描画先画面を裏にする
    try
    {
        sceneMng = new SceneManager((AbstractScene*)new Title());

    }
    catch (const char* err)
    {
        OutputDebugString(err);
        return 0;
    }
    while (ProcessMessage() == 0 && sceneMng->Update() != nullptr)
    {
        ClearDrawScreen();  //画面の初期化
        sceneMng->Draw();
        ScreenFlip();         //裏画面の内容を表画面に反映
    }

    DxLib_End();  //DXライブラリ使用の終了処理
    return 0;  //ソフトの終了
}

