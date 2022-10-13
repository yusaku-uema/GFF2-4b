#include <algorithm> // std::maxを使用するため
#define NOMINMAX
#include "DxLib.h"

//
// 当たり判定を行う関数
// 
// 緑のキャラ 左   x1
// 　　　　　 上   y1
// 　　　　　 横幅 w1
// 　　　　　 縦幅 h1
// 黄のキャラ 左   x2
// 　　　　　 上   y2
// 　　　　　 横幅 w2
// 　　　　　 縦幅 h2
//
int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int L1 = x1;      // 左
	int R1 = x1 + w1; // 右(左+横幅)
	int L2 = x2;      // 左
	int R2 = x2 + w2; // 右(左+横幅)

	if (R1 <= L2) return 0; //< 線上も当たらないことにする
	if (R2 <= L1) return 0; //< 線上も当たらないことにする

	int U1 = y1;      // 上
	int D1 = y1 + h1; // 下(上+縦幅)
	int U2 = y2;      // 上
	int D2 = y2 + h2; // 下(上+縦幅)

	if (D1 <= U2) return 0; //< 線上も当たらないことにする
	if (D2 <= U1) return 0; //< 線上も当たらないことにする

	// それ以外の場合は当たっている
	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//======================================================
	// ウインドウ設定とDXライブラリの初期化
	//======================================================
	const int SCREEN_WIDTH = 640;		//< スクリーン横の大きさ
	const int SCREEN_HEIGHT = 480;		//< スクリーン縦の大きさ

	// Windowsモードにする
	ChangeWindowMode(TRUE);
	// 画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// DXライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//初期化に失敗
		return -1;
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	//======================================================
	// ゲーム部分
	//======================================================
	//------------------------------------------------------
	// ゲーム初期化部分
	//------------------------------------------------------
	const int CHARA_WIDTH = 32;
	const int CHARA_HEIGHT = 32;

	float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;	//< 画面の中心
	float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< 画面の中心

	float yadd = 0.0f;

	int chara_act[16];
	LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90, chara_act);

	int act_motion[] = { 0, 1, 2, 1, };
	int act_index = 0;

	int MAX_MOTION_INDEX = 4; //< 0,1,2,1 の4種類 [0～3]までにするために用意

	const int ACT_SPEED = 20;
	int act_wait = ACT_SPEED;

	const int ACT_DIR_SLIDE = 3; //< 横のキャラ分スライドさせれば次の列を選択する
	int act_dir = 0;

	// マップチップロード
	const int SIZE_MAP_X = 32;  //< マップチップXサイズ
	const int SIZE_MAP_Y = 32;	//< マップチップYサイズ
	const int NUM_CHIP_X = 10;  //< 横10種類
	const int NUM_CHIP_Y = 4;   //< 縦4種類
	const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y; //< 40個
	int chip[NUM_CHIP_ALL];
	LoadDivGraph("mapchip.png", NUM_CHIP_ALL,
		NUM_CHIP_X, NUM_CHIP_Y,
		SIZE_MAP_X, SIZE_MAP_Y,
		chip);

	// マップチップを使った背景
	const int NUM_MAP_X = 20; // 32x20=640
	const int NUM_MAP_Y = 15; // 32x15=480
	int data[] = {
		// 横20x15
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,

		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,

		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,
	};

	//------------------------------------------------------
	// メインループ部分
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//裏画面消す
		ClearDrawScreen();

		// 背景
		for (int j = 0; j < NUM_MAP_Y; j++)
		{
			for (int i = 0; i < NUM_MAP_X; i++)
			{
				int no = data[i + j * NUM_MAP_X];
				if (no != 0)
				{
					DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, chip[no], FALSE);
				}
			}
		}

		// 前回の位置を覚えておく
		float old_x = x;
		float old_y = y;
		float speed = 3.0f;

		// キー情報を取得する
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		// キーで移動させる
		if (input & PAD_INPUT_RIGHT)
		{
			x += speed;
			act_dir = 2; //< 2列目を選ぶ(0スタート)
		}
		if (input & PAD_INPUT_LEFT)
		{
			x -= speed;
			act_dir = 1; //< 1列目を選ぶ(0スタート)
		}
		if (input & PAD_INPUT_A) //< キーボードならばZボタン 
		{
			yadd = -5.0f;
		}
		y += yadd;
		yadd += 0.2f;
		if (yadd > 30) yadd = 30; //< マス飛ばさないように制御

		// ブロックの当たり判定
		for (int j = 0; j < NUM_MAP_Y; j++)
		{
			for (int i = 0; i < NUM_MAP_X; i++)
			{
				int no = data[i + j * NUM_MAP_X];
				if (no >= 10 && no < 20)
				{
					if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y,
						x, y, CHARA_WIDTH, CHARA_HEIGHT))
					{
						// 上下から当たっている
						if (y != old_y)
						{
							int _y = std::max(y, old_y);
							_y /= SIZE_MAP_Y;
							_y *= SIZE_MAP_Y;
							y = _y;
							yadd = 0.0f;
						}
						else
							// 左右から当たっている
							if (x != old_x)
							{
								int _x = std::max(x, old_x);
								_x /= SIZE_MAP_X;
								_x *= SIZE_MAP_X;
								x = _x;
							}
					}
				}
			}
		}

		if (--act_wait <= 0)
		{
			act_index++;
			act_wait = ACT_SPEED;
			act_index %= MAX_MOTION_INDEX;
		}

		int motion_index = act_motion[act_index];

		// 自分のキャラを表示する
		DrawGraph(x, y, chara_act[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);

		//裏画面を表画面を入れ替える
		ScreenFlip();
	}

	//======================================================
	// DXライブラリ終了とプログラム終了
	//======================================================
	DxLib_End();
	return 0;
}
