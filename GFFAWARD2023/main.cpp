#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//キー取得用配列
	char key[256];

	//x座標
	int x = 300, y = 360, y_prev = 0, y_temp = 0;

	//ジャンプしてるかのフラグ。
	bool jflag = false;



	//グラフィックハンドル格納用配列
	int gh[16];


	//画像読み込み
	LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90, gh);

	//移動係数
	float move = 1.0f;

	//横方向と縦方向のカウント数。
	int xcount = 0, ycount = 0;
	//添字用変数
	int ix = 0, iy = 0, result = 0;


	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		if (key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {

			if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
				//移動係数を０．７１に設定
				move = 0.71f;
			}
			else {
				//斜めじゃなければ１．０に設定
				move = 1.0f;
			}
		}
		else if (key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 1.0f;
		}


		if (key[KEY_INPUT_LEFT] == 1) {
			x -= (int)4 * move;
		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			x += (int)4 * move;

		}


		//ジャンプ処理

		if (jflag == true) {
			y_temp = y;
			y += (y - y_prev) + 1;
			y_prev = y_temp;
			if (y == 360)
				jflag = false;

		}

		if (key[KEY_INPUT_SPACE] == 1 && jflag == false) {
			jflag = true;
			y_prev = y;
			y = y - 20;
		}




		if (key[KEY_INPUT_LEFT] == 1) {
			if (xcount > 0)
				xcount = 0;
			--xcount;

		}
		if (key[KEY_INPUT_RIGHT] == 1) {
			if (xcount < 0)
				xcount = 0;
			++xcount;
		}


		//カウント数から添字を求める。
		ix = abs(xcount) % 30 / 10;
		iy = abs(ycount) % 30 / 10;

		//xカウントがプラスなら右向きなので3行目の先頭添字番号を足す。
		if (xcount > 0) {
			ix += 3;
			result = ix;
		}
		else if (xcount < 0) {
			//マイナスなら左向きなので、4行目の先頭添字番号を足す。
			ix += 9;
			result = ix;
		}

		DrawGraph(x, y, gh[result], TRUE);


		//押されてなければカウントをゼロにする。
		if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
			xcount = 0;
		}

		if (key[KEY_INPUT_ESCAPE] == 1) {

			break;
		}

	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}