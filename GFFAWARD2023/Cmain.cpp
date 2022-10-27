//#include"DxLib.h"
//#include"SceneManager.h"
//#include"GameMain.h"
//
///***********************************************
// * プログラムの開始
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//    LPSTR lpCmdLine, int nCmdShow) {
//
//    // タイトルを test に変更
//    SetMainWindowText("ゲーム");
//    SetGraphMode(1280, 720, 16);  //画面サイズ
//    ChangeWindowMode(TRUE);		// ウィンドウモードで起動
//
//    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
//
//
//    SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする
//    SceneManager* sceneMng;
//    SetFontSize(20);		// 文字サイズを設定
//    try
//    {
//        sceneMng = new SceneManager((AbstractScene*)new GameMain());
//
//    }
//    catch (const char* err)
//    {
//        OutputDebugString(err);
//        return 0;
//    }
//
//    // ゲームループ
//    while (ProcessMessage() == 0 && sceneMng->Update() != nullptr) {
//
//        ClearDrawScreen();		// 画面の初期化
//        sceneMng->Draw();
//        ScreenFlip();
//    }
//
//    DxLib_End();	// DXライブラリ使用の終了処理
//
//    return 0;	// ソフトの終了
//}