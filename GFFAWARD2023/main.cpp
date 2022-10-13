
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"

#define MAP_HIGHT 20
#define MAP_WIDTH 20

/***********************************************
 * 変数
 ***********************************************/

int g_block_image[5];
int g_player_image[4];
int g_cursor_image;

int g_cursorx = 0;
int g_cursory = 0;
int g_cursor_speed = 0;
int g_old_key;
int g_now_key;

bool g_AKey = FALSE;
bool g_hanten = false;
int g_playerx = 2 * 30;
int g_playery = 7 * 30;
int g_player_hight = 60;
int g_player_width = 30;

int g_player_angle = 0;

int g_player_image_type = 0;
int g_image_time = 0;

int g_jump_startx;
int g_jump_starty;

int g_jump = 0;
int g_jumpy;
int g_jump_radius = 16;
int g_jump_centerx;
int g_jump_centery;
int g_jump_angle = 10;

int g_playerx_radius = 30 / 2;
int g_playery_radius = 60 / 2;

unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,4},
        {4,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,4},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
};
unsigned int PLAYER_MAP[MAP_HIGHT][MAP_WIDTH];
unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];

/***********************************************
 * 関数プロトタイプ宣言
 ***********************************************/
int LoadImages();  //画像読み込み
void Player();  //自機操作
void Stage();  //ステージ
void Sky(void); //空
void Enemy(void); //敵
void Sousa(void); // 操作
void Jump(void); //ジャンプ
void Walk(void);

/***********************************************
 * プログラム開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("ゲーム");  //タイトルを設定

    SetGraphMode(600, 600, 16);
    ChangeWindowMode(TRUE);		               // ウィンドウモードで起動

    if (DxLib_Init() == -1) return -1;	   // DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);	           // 描画先画面を裏にする

    if (LoadImages() == -1) return -1;  //画像読み込み関数を呼び出し

    for (int i = 0; i < MAP_HIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            MAP_DATA[i][j] = MAP_DATA_INIT[i][j];
            PLAYER_MAP[i][j] = 0;
        }
    }
    PLAYER_MAP[g_playery / 30][g_playerx / 30] = 1;
    PLAYER_MAP[(g_playery / 30) + 1][g_playerx / 30] = 1;

    while (ProcessMessage() == 0)
    {
        ClearDrawScreen();  //画面の初期化


        Stage();
        Player();
        Sousa();

        ScreenFlip();         //裏画面の内容を表画面に反映
    }

    DxLib_End();  //DXライブラリ使用の終了処理
    return 0;  //ソフトの終了
}




/***********************************************
* ステージ描画
***********************************************/
void Stage()
{
    for (int i = 0; i < MAP_HIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            DrawGraph(30 * j, 30 * i, g_block_image[MAP_DATA[i][j]], TRUE);
            //DrawFormatString(14 * j, 14 * i, 0xffffff, "%d", PLAYER_MAP[i][j]);
            DrawFormatString(14 * j, 14 * i, 0xffffff, "%d", MAP_DATA[i][j]);
            PLAYER_MAP[i][j] = 0;
        }
    }
}

void Sousa(void)
{
    if (!CheckHitKey(KEY_INPUT_LEFT) && !CheckHitKey(KEY_INPUT_RIGHT) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN))g_old_key = 0;
    if (!CheckHitKey(KEY_INPUT_A))g_AKey = FALSE;

    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        g_now_key = KEY_INPUT_LEFT;
        if (g_now_key == g_old_key)
        {
            g_cursor_speed++;
            if (g_cursor_speed >= 10)
            {
                g_cursor_speed = 0;
                if (g_cursorx > 0)g_cursorx--;
            }
        }
        else if (g_old_key == 0)
        {
            g_cursor_speed = 0;
            if (g_cursorx > 0)g_cursorx--;
        }
        g_old_key = KEY_INPUT_LEFT;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        g_now_key = KEY_INPUT_RIGHT;
        if (g_now_key == g_old_key)
        {
            g_cursor_speed++;
            if (g_cursor_speed >= 10)
            {
                g_cursor_speed = 0;
                if (g_cursorx < 19)g_cursorx++;
            }
        }
        else if (g_old_key == 0)
        {
            g_cursor_speed = 0;
            if (g_cursorx < 19)g_cursorx++;
        }
        g_old_key = KEY_INPUT_RIGHT;
    }
    if (CheckHitKey(KEY_INPUT_UP))
    {
        g_now_key = KEY_INPUT_UP;
        if (g_now_key == g_old_key)
        {
            g_cursor_speed++;
            if (g_cursor_speed >= 10)
            {
                g_cursor_speed = 0;
                if (g_cursory > 0)g_cursory--;
            }
        }
        else if (g_old_key == 0)
        {
            g_cursor_speed = 0;
            if (g_cursory > 0)g_cursory--;
        }
        g_old_key = KEY_INPUT_UP;
    }
    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        g_now_key = KEY_INPUT_DOWN;
        if (g_now_key == g_old_key)
        {
            g_cursor_speed++;
            if (g_cursor_speed >= 10)
            {
                g_cursor_speed = 0;
                if (g_cursory < 19)g_cursory++;
            }
        }
        else if (g_old_key == 0)
        {
            g_cursor_speed = 0;
            if (g_cursory < 19)g_cursory++;
        }
        g_old_key = KEY_INPUT_DOWN;
    }

    if (CheckHitKey(KEY_INPUT_A))
    {
        if (g_AKey == FALSE)
        {
            if (/*MAP_DATA[g_cursory][g_cursorx] == 0 &&*/ PLAYER_MAP[g_cursory][g_cursorx] == 0)MAP_DATA[g_cursory][g_cursorx] = 2;
            //else if (MAP_DATA[g_cursory][g_cursorx] != 0)MAP_DATA[g_cursory][g_cursorx] = 0;
        }
        g_AKey = TRUE;
    }

    DrawGraph(30 * g_cursorx, 30 * g_cursory, g_cursor_image, TRUE);
}

void Player()
{
    if (MAP_DATA[(g_playery / 30) + 2][g_playerx / 30] == 2 || g_jump > 0)Jump();
    else Walk();

    if ((g_playery / 30) + 1 < MAP_HIGHT)
    {
        PLAYER_MAP[g_playery / 30][g_playerx / 30] = 1;
        PLAYER_MAP[(g_playery / 30) + 1][g_playerx / 30] = 1;
        PLAYER_MAP[g_playery / 30][g_playerx / 30 + 1] = 2;
        PLAYER_MAP[(g_playery / 30) + 1][g_playerx / 30 + 1] = 2;
    }

    g_image_time++;
    if (g_image_time >= 8)
    {
        g_player_image_type++;
        g_image_time = 0;
        if (g_player_image_type >= 4)g_player_image_type = 0;
    }

    DrawFormatString(0, 500, 0xffffff, "x = %d", g_playery / 30);
    DrawRotaGraph(g_playerx + g_playerx_radius, g_playery + g_playery_radius, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_hanten);
}

void Walk(void)
{
    if (g_hanten == FALSE)
    {
        if (MAP_DATA[(g_playery / 30) + 2][g_playerx / 30] > 0)//足元が穴じゃなければ
        {
            if (MAP_DATA[g_playery / 30][(g_playerx + g_player_width) / 30] > 0 || MAP_DATA[(g_playery / 30) + 1][(g_playerx + g_player_width) / 30] > 0)g_hanten = true;
            else  g_playerx++;
        }
        else g_playery += 3; //足元が穴なら落ちる
    }
    else
    {
        if (MAP_DATA[(g_playery / 30) + 2][(g_playerx / 30) + 1] > 0)//足元が穴じゃなけば
        {
            if (MAP_DATA[g_playery / 30][(g_playerx - 1) / 30] > 0 || MAP_DATA[(g_playery / 30) + 1][(g_playerx - 1) / 30] > 0)g_hanten = false;
            else g_playerx--;
        }
        else g_playery += 3;
    }
}

void Jump(void)
{
    switch (g_jump)
    {
    case 0:
        g_jump_starty = g_playery;
        g_jump = 1;
        break;

    case 1:
        g_playery -= 5;

        if (g_jump_starty - g_playery >= 90)
        {
            g_playery = g_jump_starty - (30 * 3);
            g_jump_centerx = g_playerx + g_jump_radius;
            g_jump_centery = g_playery;
            g_jump_angle = 180;
            g_jump = 2;
        }

        //g_enemyy = (sin(g_enemy_angle * M_PI / 180) * g_enemy_radius) + g_centery;
        //g_enemyx = (cos(g_enemy_angle * M_PI / 180) * g_enemy_radius) + g_centerx;

        break;
    case 2:

        g_playery = (sin(g_jump_angle * M_PI / 180) * g_jump_radius) + g_jump_centery;
        g_playerx = (cos(g_jump_angle * M_PI / 180) * g_jump_radius) + g_jump_centerx;
        g_jump_angle += 10;
        if (g_jump_angle >= 360)g_jump_angle = 0, g_jump = 0;

        break;

    case 3:
        g_jump = 0;
        break;
    }

    DrawFormatString(300, 300, 0xffffff, "%d アングル", g_jump);



    //g_enemyy = (sin(g_enemy_angle * M_PI / 180) * g_enemy_radius) + g_centery;
}

/***********************************************
* 画像読み込み
***********************************************/
int LoadImages()
{
    //if ((g_player_image = LoadGraph("images/human.png")) == -1) return -1;
    if ((g_cursor_image = LoadGraph("images/cursor .png")) == -1) return -1;
    if (LoadDivGraph("images/block/stage3.png", 5, 5, 1, 30, 30, g_block_image) == -1) return -1;
    if (LoadDivGraph("images/player/human.png", 4, 4, 1, 30, 60, g_player_image) == -1) return -1;
}



