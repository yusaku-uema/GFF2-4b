#include"DxLib.h"
#include"main.h"
#include"character.h"
#include"map.h"

#define MAP_NUM 1 //マップの数

#define MAP_SIZE 32 //マップチップーつのドット

#define MAP_WIDTH_MAX 40 //マップの最大横幅
#define MAP_HEIGHT_MAX 40 //マップの最大縦長さ

#define MOVE_FRAME 15 //移動にかけるフレーム数

int CharacterImages[16]; //少年のイメージ画像
int background1; //背景画像
int blockImages; //ブロック画像
int MapNo; //マップの数
int Key; //キー入力
int ScrollX, ScrollY;
int MoveX, MoveY;
int Move;
int PlayerY, PlayerX;
int MoveCounter;

Character character;

#define MAP_NUM 1 //マップの数

#define MAP_SIZE 32 //マップチップーつのドット

#define MAP_WIDTH_MAX 40 //マップの最大横幅
#define MAP_HEIGHT_MAX 40 //マップの最大縦長さ

#define MOVE_FRAME 15 //移動にかけるフレーム数

void GraphDraw(int ScrollX, int ScrollY);


// マップの構造体
struct MAPDATA
{
    // マップの幅
    int Width;

    // マップの高さ
    int Height;

    // マップ
    int Data[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
};

// マップのデータ
MAPDATA MapData[MAP_NUM] =
{
    // マップ０
    {
        40,
        32,
        {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 1, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } ,
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 1, 0, 0, 0, 1, 0, 0 } ,
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 0, 1, 1, 1, 0, 0 } ,

            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 1, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 0, 1, 1, 0, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 1, 1, 0, 0, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 1, 1, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  0, 0, 0, 1, 0, 1, 1, 1, 1, 0 } ,

            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 0, 1, 0, 1, 0, 0, 0, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 0, 1, 0, 1, 0, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 1, 1, 1, 0, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 0, 0, 0, 0, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 0, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 0, 1, 0 } ,

            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 1, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 0, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 1, 1, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } ,
            { 0, 1, 1, 0, 0, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 0, 0, 1, 1 ,  1, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
        }
    },
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // タイトル
    SetMainWindowText("プロトタイプ版"); //ゲームタイトル
	SetOutApplicationLogValidFlag(FALSE);   //ログ出力を無効にする
	ChangeWindowMode(TRUE);// ウィンドウモードで起動
	SetGraphMode(1280, 720, 0); //画面サイズ
    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理
	if (LoadImages() == -1)return -1; //画像読込み
	

    // 描画先画面を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // プレイヤーの初期位置をセット
    PlayerX = 1;
    PlayerY = 1;

    // 最初は停止中(0)にしておく
    Move = 0;

    // ループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面を初期化
        ClearDrawScreen();

        
        // 移動中ではない場合キー入力を受け付ける
        if (Move == 0)
        {
            // キー入力を得る
            Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

            // キー入力に応じてプレイヤーの座標を移動
            if (Key & PAD_INPUT_LEFT)
            {
                Move = 1;
                MoveX = -1;
                MoveY = 0;
            }
            if (Key & PAD_INPUT_RIGHT)
            {
                Move = 1;
                MoveX = 1;
                MoveY = 0;
            }
            if (Key & PAD_INPUT_UP)
            {
                Move = 1;
                MoveX = 0;
                MoveY = -1;
            }
            if (Key & PAD_INPUT_DOWN)
            {
                Move = 1;
                MoveX = 0;
                MoveY = 1;
            }

            // 進入不可能なマップだった場合は移動できない
            if (Move == 1)
            {
                if (MapData[MapNo].Data[PlayerY + MoveY][PlayerX + MoveX] == 0)
                {
                    Move = 0;
                }
                else
                {
                    MoveCounter = 0;
                }
            }

            // 停止中は画面のスクロールは行わない
            ScrollX = 0;
            ScrollY = 0;
        }

        // 移動中の場合は移動処理を行う
        if (Move == 1)
        {
            MoveCounter++;

            // 移動処理が終了したら停止中にする
            if (MoveCounter == MOVE_FRAME)
            {
                Move = 0;

                // プレイヤーの位置を変更する
                PlayerX += MoveX;
                PlayerY += MoveY;

                // 停止中は画面のスクロールは行わない
                ScrollX = 0;
                ScrollY = 0;
            }
            else
            {
                // 経過時間からスクロール量を算出する
                ScrollX = -(MoveX * MAP_SIZE * MoveCounter / MOVE_FRAME);
                ScrollY = -(MoveY * MAP_SIZE * MoveCounter / MOVE_FRAME);
            }
        }

        // マップとプレイヤーを描画
        GraphDraw(ScrollX, ScrollY);

        // 裏画面の内容を表画面に映す
        ScreenFlip();
    }

    DxLib_End();               // ＤＸライブラリ使用の終了処理

    return 0;                  // ソフトの終了
}

int LoadImages(void) { //画像読込み
	if (LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90,CharacterImages) == 1)return -1; //少年仮
	if((background1 = LoadGraph("images/background/street003_day.png")) == -1)return -1;// 背景
	if ((blockImages = LoadGraph("images/block/0115_s1.png")) == -1)return -1; //ブロック
	
}

int GetArrayImages(int type, int num) { //type,使いたい画像の要素数を指定することで、指定した画像が使える
	switch (type)
	{
	case CharacterImage: //少年
		if (0 <= num && num <= 16) {
			return CharacterImages[num];
		}
		else { return -1; }
		break;
	}
}


// マップとプレイヤーの描画関数
void GraphDraw(int ScrollX, int ScrollY)
{
    int j, i;
    int MapDrawPointX, MapDrawPointY;     // 描画するマップ座標値
    int DrawMapChipNumX, DrawMapChipNumY; // 描画するマップチップの数

    // 描画するマップチップの数をセット
    DrawMapChipNumX = 1280 / MAP_SIZE + 2;
    DrawMapChipNumY = 720 / MAP_SIZE + 2;

    // 画面左上に描画するマップ座標をセット
    MapDrawPointX = character.getCharacter_X() - (DrawMapChipNumX / 2 - 1);
    MapDrawPointY = character.getCharacter_Y() - (DrawMapChipNumY / 2 - 1);

    // マップを描く
    for (i = -1; i < DrawMapChipNumY; i++)
    {
        for (j = -1; j < DrawMapChipNumX; j++)
        {
            // 画面からはみ出た位置なら描画しない
            if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
                j + MapDrawPointX >= MapData[MapNo].Width || i + MapDrawPointY >= MapData[MapNo].Height) continue;

            // マップデータが０だったら四角を描画する
            if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 0)
            {
                 DrawBox(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY,
                     j * MAP_SIZE + MAP_SIZE + ScrollX, i * MAP_SIZE + MAP_SIZE + ScrollY,
                     GetColor(255, 0, 0), TRUE);
            }
        }
    }
}