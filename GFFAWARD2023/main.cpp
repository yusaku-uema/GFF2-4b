#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"
#include"UI.h"

#define MAP_HIGHT 20
#define MAP_WIDTH 103

#define DRAW_MAP_HIGHT 20
#define DRAW_MAP_WIDTH 35

#define BLOCK_WIDTH 30
//#define PLAYER_HIGHT 30

/***********************************************
 * 変数
 ***********************************************/

int g_block_image[12];
int g_item_image[2];
int g_player_image[4];
int g_cursor_image;
int g_white_image;
//int g_jump_image;
int g_haikei_image;
bool A_check = false; //Aボタン押されたか
bool Enemycheck = false; //敵、TRUE停止中
bool A_check1 = false; //Aボタン押されたか
bool Enemycheck1 = false; //敵、TRUE停止中

int time,time1;
int fps, fps1;

int g_block_quantity =20;//ブロック個数

int g_stage_count = 0;
int g_hammer; //ハンマー

int g_player_hit_lowerbody_front = 0; //プレイヤーが当たった障害物
int g_player_hit_upperbody_front = 0;
int g_player_hit_lowerbody_back = 0; //プレイヤーが当たった障害物
int g_player_hit_upperbody_back = 0;

int g_player_hit_under_back = 1;
int g_player_hit_under_front = 1;

int g_uicursorx = 0;
bool g_uicursor = FALSE;
bool g_stage_scroll = FALSE;
int g_stage_x = 0;

int g_cursorx = 7;
int g_cursory = 15;
int g_cursor_speed = 0;
int g_old_key = 0;
int g_now_key = 0;

bool g_AKey = FALSE;
bool g_direction = false; //false = 右向き　true = 左向き
int g_playerx = 1 * 30;
int g_playery = 7 * 30;

int g_player_speed = 1;

int g_player_angle = 0;

int g_player_image_type = 0;
int g_image_time = 0;

int g_jump = 0;

int g_jump_centerx;
int g_jump_centery;
int g_jump_angle = 0;

int g_playerx_radius = 30 / 2;
int g_playery_radius = 60 / 2;

int g_EnemyImage[4];

int g_stage_item_quantity = 4;

int g_enemy_hit_lowerbody_front = 0; //プレイヤーが当たった障害物
int g_enemy_hit_upperbody_front = 0;
int g_enemy_hit_lowerbody_back = 0; //プレイヤーが当たった障害物
int g_enemy_hit_upperbody_back = 0;
int g_enemy_hit_under_back = 1;
int g_enemy_hit_under_front = 1;
bool g_Edirection = true; //false = 右向き　true = 左向き
int g_enemy_image[4];
int g_enemyx = 68 * 30;
int g_enemyy = 16 * 30;
int g_enemy_hight = 60;
int g_enemy_width = 30;
int g_enemy_speed = 1;
int g_enemy_angle = 0;
int g_enemy_image_type = 0;
int g_enemyx_radius = 30 / 2;
int g_enemyy_radius = 60 / 2;
int g_enemy_time = 0;

int g_enemy2_hit_lowerbody_front = 0; //プレイヤーが当たった障害物
int g_enemy2_hit_upperbody_front = 0;
int g_enemy2_hit_lowerbody_back = 0; //プレイヤーが当たった障害物
int g_enemy2_hit_upperbody_back = 0;
int g_enemy2_hit_under_back = 1;
int g_enemy2_hit_under_front = 1;
bool g_Edirection2 = true; //false = 右向き　true = 左向き
int g_enemy2_image[4];
int g_enemy2x = 68 * 30;
int g_enemy2y = 12 * 30;
int g_enemy2_hight = 60;
int g_enemy2_width = 30;
int g_enemy2_speed = 2;
int g_enemy2_angle = 0;
int g_enemy2_image_type = 0;
int g_enemy2x_radius = 30 / 2;
int g_enemy2y_radius = 60 / 2;
int g_enemy2_time = 0;
bool g_forcedtermination; //強制終了
unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,5,0,0,5,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,5,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,5,5,5,5,0,5,0,0,5,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,5,0,5},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,1,1,1,1,1,1,1,1,0,5,5,5,5,0,0,0,0,0,0,5,0,0,0,0,5,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,7,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,3,6,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,0,0,1,0,0,0,1,1,7,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,6,0,0,1,1,6,0,0,0,0,0,0,0,0,0,3,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,1,1,7,0,0,0,0,0,0,0,0,0,4,1,1,1,1,1,1,1,7,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {6,0,0,0,0,0,0,0,6,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {7,0,0,0,0,0,0,0,1,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {3,1,7,3,1,7,1,7,1,1,3,5,5,3,1,1,5,1,7,5,3,3,1,7,1,3,3,1,7,3,1,5,1,1,3,3,7,7,3,3,3,1,1,7,7,5,1,5,7,7,1,1,3,7,1,1,1,7,7,1,7,1,1,7,7,7,3,3,1,1,3,3,1,7,7,3,3,1,1,1,7,7,3,7,7,1,1,3,1,3,7,7,5,5,1,1,3,7,7,5,5,1,1},
        {1,3,5,7,3,5,7,1,5,7,5,1,1,5,7,7,3,3,1,1,3,1,3,7,7,5,5,1,1,3,7,7,5,5,1,1,3,3,1,1,7,3,7,1,1,3,5,3,5,5,7,7,1,1,5,7,3,1,3,1,7,3,1,7,3,1,5,5,7,7,1,1,5,3,3,1,1,7,7,3,1,5,1,3,7,1,7,7,1,1,5,3,3,1,1,7,7,3,1,5,1,3,7},
};
unsigned int PLAYER_MAP[MAP_HIGHT][MAP_WIDTH];
unsigned int ENEMY_MAP[MAP_HIGHT][MAP_WIDTH];
unsigned int MAP_DATA[MAP_HIGHT][MAP_WIDTH];

/***********************************************
 * 関数プロトタイプ宣言
 ***********************************************/
int LoadImages();  //画像読み込み
void Player();  //自機操作
void Stage();  //ステージ
void  UI(void); //UI
void Enemy(void); //敵
void Enemy2(void); //敵
void Enemy3(void); //敵
void Sousa(void); // 操作
void Jump(void); //ジャンプ
void Walk(void);

int HitBoxPlayer();
int HitBoxPlayer2();
/***********************************************
 * プログラム開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("ゲーム");  //タイトルを設定

    SetGraphMode(1280, 720, 16);
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

    while (ProcessMessage() == 0 && g_forcedtermination != true)
    {
        ClearDrawScreen();  //画面の初期化


        if (g_stage_scroll == FALSE)Sousa();
        Stage();
        Player();
        Enemy();
        Enemy2();
        UI();
        ui.UIDraw();
        ui.ClockNeedleMove();
        /*ui.GameOver();*/

        ScreenFlip();         //裏画面の内容を表画面に反映
        if (GetJoypadInputState(DX_INPUT_PAD1)& PAD_INPUT_7){
            g_forcedtermination = true;
        }
    }

    DxLib_End();  //DXライブラリ使用の終了処理
    return 0;  //ソフトの終了
}


/***********************************************
* UI
***********************************************/
void UI(void)
{
    int a = (1280 - (150 * (g_stage_item_quantity - 1))) / 2;
    
    for (int i = 0; i < 4; i++)
    {
        DrawRotaGraph(a + (150 * i), 660, 1.0, M_PI / 180 * 0, g_white_image, TRUE, FALSE);
       if(i == 1) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[0], TRUE, FALSE);
       if (i == 0) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_block_image[1], TRUE, FALSE);
       if (i == 2) DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[1], TRUE, FALSE);
       if (i == 3)DrawRotaGraph(a + (150 * i), 660, 3.0, M_PI / 180 * 0, g_hammer, TRUE, FALSE);
       if(i == g_uicursorx)DrawRotaGraph(a + (150 * i), 660, 3.3, M_PI / 180 * 0, g_cursor_image, TRUE, FALSE);
    }
}

/***********************************************
* ステージ描画
***********************************************/
void Stage()
{
    SetDrawArea(115, 0, 1165, 600);

    DrawGraph(0 - (g_stage_x / 5), 0, g_haikei_image, FALSE);

    for (int i = 0; i < MAP_HIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            

            if (MAP_DATA[i][j] != 0)
            {
                if (MAP_DATA[i][j] <= g_block_quantity)DrawGraph(115 + (30 * j) - g_stage_x, 30 * i, g_block_image[MAP_DATA[i][j]], TRUE);
                else DrawGraph(115 + (BLOCK_WIDTH * j) - g_stage_x, BLOCK_WIDTH * i, g_item_image[MAP_DATA[i][j] -  (g_block_quantity + 1)], TRUE);
            }
            if(g_stage_scroll == FALSE)DrawGraph(115 + (30 * g_cursorx), 30 * g_cursory, g_cursor_image, TRUE);

            

            PLAYER_MAP[i][j] = 0;
            //DrawFormatString(14 * j, 14 * i, 0xffffff, "%d", MAP_DATA[i][j]);
            //DrawLine(0, 30 * i, MAP_WIDTH * 30, 30 * i, 0xffffff, TRUE);
            //DrawLine(30 * j, 0, 30 * j, MAP_HIGHT * 30, 0xffffff, TRUE);
           
        }
    }


    SetDrawArea(0, 0, 1280, 720);

    if (g_stage_scroll == TRUE)
    {
        if (g_direction == FALSE)
        {
            g_stage_x += 10;
            if (g_stage_x > ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH) * (g_stage_count + 1))
            {
                g_stage_x = ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH) * (g_stage_count + 1);
                g_stage_scroll = FALSE;
                g_stage_count++;

                g_cursorx = 3, g_cursory = 15;
            }
        }

        else
        {
            g_stage_x -= 10;
            if (g_stage_x < ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH) * (g_stage_count - 1))
            {
                g_stage_x = ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH) * (g_stage_count - 1);
                g_stage_scroll = FALSE;
                g_stage_count--;

                g_cursorx = 30, g_cursory = 15;
            }
        }
    }
}

void Sousa(void)
{
    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) && 
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) && 
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) && 
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))g_old_key = 0;

    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))g_AKey = FALSE;

    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) && !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)) g_uicursor = FALSE;

    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) || 
        (GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_RIGHT) ||
        (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) ||
        (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))
    {
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) g_now_key = PAD_INPUT_LEFT;
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) g_now_key = PAD_INPUT_RIGHT;
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) g_now_key = PAD_INPUT_UP;
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) g_now_key = PAD_INPUT_DOWN;

        if (g_now_key == g_old_key) g_cursor_speed++;
        if (g_cursor_speed >= 10 || g_old_key == 0)
        {
            g_cursor_speed = 0;
            if (g_now_key == PAD_INPUT_LEFT && g_cursorx > 0)g_cursorx--;
            if (g_now_key == PAD_INPUT_RIGHT && g_cursorx < DRAW_MAP_WIDTH - 1)g_cursorx++;
            if (g_now_key == PAD_INPUT_UP && g_cursory > 0)g_cursory--;
            if (g_now_key == PAD_INPUT_DOWN && g_cursory < DRAW_MAP_HIGHT - 1)g_cursory++;
        }
       
        g_old_key = g_now_key;
    }

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
    {
        if (g_AKey == FALSE)
        {
            if (MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 0 && PLAYER_MAP[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 0)
            {
                if(g_uicursorx == 1 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] > 0 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] <= g_block_quantity) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = g_block_quantity + 1; //トランポリンを追加
                if (g_uicursorx == 0 && MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 0) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 2; //ブロックを追加
            }

            if (g_uicursorx == 2 && (MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 2 || MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == g_block_quantity + 1)) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 0; // 消しゴムの処理

            //else if (MAP_DATA[g_cursory][g_cursorx] != 0)MAP_DATA[g_cursory][g_cursorx] = 0;
        }
        g_AKey = TRUE;
    }

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)
    {
        if (g_uicursor == FALSE)
        {
            if (g_uicursorx > 0)g_uicursorx--;
            else g_uicursorx = g_stage_item_quantity - 1;
            g_uicursor = TRUE;
        }
    }
    else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)
    {
        if (g_uicursor == FALSE)
        {
            if (g_uicursorx < g_stage_item_quantity - 1)g_uicursorx++;
            else g_uicursorx = g_uicursorx = 0;
            g_uicursor = TRUE;
        }
    }
}

void Player()
{
    if (g_direction == FALSE)
    {
        g_player_hit_under_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][g_playerx / BLOCK_WIDTH];
        g_player_hit_under_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
        g_player_hit_lowerbody_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH]; 
        g_player_hit_upperbody_front = MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_player_hit_lowerbody_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][g_playerx / BLOCK_WIDTH];
        g_player_hit_upperbody_back = MAP_DATA[g_playery / BLOCK_WIDTH][g_playerx / BLOCK_WIDTH];
    }
    else
    {
        g_player_hit_under_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
        g_player_hit_under_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][g_playerx / BLOCK_WIDTH];
        g_player_hit_lowerbody_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][g_playerx / BLOCK_WIDTH];
        g_player_hit_upperbody_front = MAP_DATA[g_playery / BLOCK_WIDTH][g_playerx / BLOCK_WIDTH];
        g_player_hit_lowerbody_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_player_hit_upperbody_back = MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
    }


    if (g_stage_scroll == FALSE)
    {
        if ((g_player_hit_lowerbody_back == g_block_quantity + 1) || g_jump > 0)Jump();
        else Walk();

        if ((g_playerx >= (BLOCK_WIDTH * (DRAW_MAP_WIDTH - 1)) * (g_stage_count + 1) && g_direction == FALSE) ||
            (g_playerx <= (BLOCK_WIDTH * (DRAW_MAP_WIDTH - 1)) * g_stage_count) && g_direction == TRUE)
        {
            g_stage_scroll = TRUE;
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;
            else ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH)* BLOCK_WIDTH;
        }

        if ((g_playery / BLOCK_WIDTH) + 1 < MAP_HIGHT && (g_playery / BLOCK_WIDTH) > 0)
        {
            PLAYER_MAP[g_playery / BLOCK_WIDTH][g_playerx / BLOCK_WIDTH] = 1;
            PLAYER_MAP[(g_playery / BLOCK_WIDTH) + 1][g_playerx / BLOCK_WIDTH] = 1;
            PLAYER_MAP[g_playery / BLOCK_WIDTH][g_playerx / BLOCK_WIDTH + 1] = 2;
            PLAYER_MAP[(g_playery / BLOCK_WIDTH) + 1][g_playerx / BLOCK_WIDTH + 1] = 2;
        }

        g_image_time++;
        if (g_image_time >= 8)
        {
            g_player_image_type++;
            g_image_time = 0;
            if (g_player_image_type >= 4)g_player_image_type = 0;
        }
    }

    //DrawFormatString(0, 500, 0xffffff, "x = %d", g_playery / 30);
    DrawFormatString(0, 500, 0xffffff, "x = %d", time);
    DrawRotaGraph(115 + (g_playerx + 15) - g_stage_x, g_playery + 30, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_direction);
}

void Walk(void)
{
    if (g_player_hit_under_back > 0 && g_player_hit_under_back <= g_block_quantity) //地面が穴じゃなかったら
    {
        g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのy座標を整える

        if ((g_player_hit_lowerbody_front == 0 || g_player_hit_lowerbody_front > g_block_quantity) && (g_player_hit_upperbody_front == 0 || g_player_hit_upperbody_front > g_block_quantity))//障害物に当たってないとき
        {
            if (g_direction == FALSE)g_playerx += g_player_speed; 
            else g_playerx -= g_player_speed;
        }
        else //障害物に当たった時
        {
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;
            else  g_playerx = ((g_playerx / BLOCK_WIDTH) + 1) * BLOCK_WIDTH;

            if ((MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx + BLOCK_WIDTH) / BLOCK_WIDTH] == 0 || MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx + BLOCK_WIDTH) / BLOCK_WIDTH] > g_block_quantity) && (MAP_DATA[(g_playery / BLOCK_WIDTH)][(g_playerx + BLOCK_WIDTH) / BLOCK_WIDTH] == 0 || MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx + BLOCK_WIDTH) / BLOCK_WIDTH] > g_block_quantity) && g_direction == TRUE || //後ろが障害物じゃなかったら
                (MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx - 1) / BLOCK_WIDTH] == 0 || MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx - 1) / BLOCK_WIDTH] > g_block_quantity) && (MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx - 1) / BLOCK_WIDTH] == 0 || MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx - 1) / BLOCK_WIDTH] > g_block_quantity) && g_direction == FALSE)
            {
                if (g_direction == FALSE)g_direction = TRUE; //進行方向を逆にする
                else  g_direction = FALSE;
            }
        }
    }

    else
    {
        if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;  //キャラを穴の真ん中にする
        else g_playerx = ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
        g_playery += 5; //キャラを落とす
    }

    if (HitBoxPlayer())
    {
        g_playerx -= 22 * 30;


        /*if (g_direction == FALSE)g_direction = TRUE;
        else g_direction = FALSE;*/
    }
    if(HitBoxPlayer2())  g_playerx -= 22 * 30;;

}

void Jump(void)
{
    switch (g_jump)
    {
    case 0:
        g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH; //x座標を整える
        g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //y座標を整える
        g_jump_centery = g_playery; //円を描いてジャンプするための中心座標yを設定
        if (g_direction == FALSE)g_jump_centerx = g_playerx + (BLOCK_WIDTH / 2), g_jump_angle = 180; //中心座標ｘとジャンプするための現在の角度を設定
        else g_jump_centerx = g_playerx - (BLOCK_WIDTH / 2), g_jump_angle = 0; //中心座標ｘとジャンプするための現在の角度を設定
        g_jump = 1;
        break;

    case 1:
        if (g_direction == FALSE) g_jump_angle += 4; //円を描くためのアングルを加算
        else g_jump_angle -= 4; ////円を描くためのアングルを減算

        g_playery = (sin(g_jump_angle * M_PI / 180) * 90) + g_jump_centery; //円を描くためのy座標を計算
        g_playerx = (cos(g_jump_angle * M_PI / 180) * 15) + g_jump_centerx; //円を描くためのx座標を計算

        if ((g_jump_angle >= 360 || g_jump_angle <= -180) && g_jump == 1) //ブロックなどに当たらなかったら
        {
            g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH; //x座標を整える
            g_jump = 0;
            DrawFormatString(10, 10, 0xffffff, "02");
        }

        else if((g_jump_angle >= 240 || g_jump_angle <= -60) && g_jump == 1)
        {

            if ((g_jump_angle >= 270 || g_jump_angle <= -90) && g_jump == 1) //ジャンプして、落ち始めたら
            {
                if (g_player_hit_under_front > 0 && g_player_hit_under_front <= g_block_quantity)
                {
                    g_jump = 2;
                    g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのｙ座標を整える
                    DrawFormatString(10, 10, 0xffffff, "01");
                }
            }

            else if ((g_player_hit_upperbody_front > 0 && g_player_hit_upperbody_front <= g_block_quantity) || (g_player_hit_lowerbody_front > 0 && g_player_hit_lowerbody_front <= g_block_quantity))
            {
                if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;
                else g_playerx = ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
                g_jump = 0;
            }
        }

        if ((g_player_hit_upperbody_back > 0 && g_player_hit_upperbody_back <= g_block_quantity) && g_jump == 1)
        {
            if (g_direction == FALSE)g_playerx = g_playerx / BLOCK_WIDTH * BLOCK_WIDTH;
            else g_playerx = (g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH * BLOCK_WIDTH;
            g_jump = 0;
        }
        break;

    case 2:

        if (g_direction == FALSE)g_playerx += g_player_speed;
        else g_playerx -= g_player_speed;

        if (g_player_hit_under_back > 0 && g_player_hit_under_back <= g_block_quantity)
        {
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;
            else g_playerx = ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
            g_jump = 0;
        }
        break;
    }

    //DrawFormatString(300, 300, 0xffffff, "%d アングル", g_jump_endy);
}
void Enemy()
{
    if (g_stage_scroll == FALSE)
    {
        if (Enemycheck == true) {
            g_enemy_speed = 0;
            fps++;
        }
        if (Enemycheck == true && fps % 60 == 0) {  //fps 60 で一秒
            time++;
        }

        if (g_Edirection == FALSE && Enemycheck == false)
        {
            g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
            g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
            g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
            g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
        }
        else if (g_Edirection == TRUE && Enemycheck == false)
        {
            g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
            g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
            g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
            g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
            g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        }

        if (g_enemy_hit_under_back > 0 && g_enemy_hit_under_back < 10 && Enemycheck == false)
        {
            g_enemyy = (g_enemyy / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのy座標を整える

            if ((g_enemy_hit_lowerbody_front == 0 || g_enemy_hit_lowerbody_front >= g_block_quantity) && (g_enemy_hit_upperbody_front == 0 || g_enemy_hit_upperbody_front >= g_block_quantity))
            {
                if (g_Edirection == FALSE)g_enemyx += g_enemy_speed; //障害物に当たってなかったら進む
                else g_enemyx -= g_enemy_speed;
            }
            else
            {
                if (g_Edirection == FALSE)g_enemyx = (g_enemyx / BLOCK_WIDTH) * BLOCK_WIDTH, g_Edirection = TRUE; //プレイヤーがめり込んでるかもしれないからx座標を調整する
                else  g_enemyx = ((g_enemyx / BLOCK_WIDTH) + 1) * BLOCK_WIDTH, g_Edirection = FALSE;
            }
        }
        else if (Enemycheck == false)
        {
            if (g_direction == FALSE)g_enemyx = (g_enemyx / BLOCK_WIDTH) * BLOCK_WIDTH;  //キャラを穴の真ん中にする
            else g_enemyx = ((g_enemyx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
            g_enemyy += 5; //キャラを落とす
        }
        if (HitBoxPlayer())
        {
            if (g_Edirection == FALSE)
            {
                g_Edirection = TRUE;
            }
            else
            {
                g_Edirection = FALSE;
            }
        }
        if ((g_enemyx >= 68 * 30) && (g_Edirection == FALSE))g_Edirection = TRUE;//範囲指定
        if ((g_enemyx <= 58 * 30) && (g_Edirection == TRUE))g_Edirection = FALSE;//範囲指定
        if ((g_enemyy / BLOCK_WIDTH) + 1 < MAP_HIGHT)
        {
            ENEMY_MAP[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH] = 1;
            ENEMY_MAP[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH] = 1;
            ENEMY_MAP[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH + 1] = 2;
            ENEMY_MAP[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH + 1] = 2;
        }

        g_enemy_time++;
        if (g_enemy_time >= 8)
        {
            g_enemy_image_type++;
            g_enemy_time = 0;
            if (g_enemy_image_type >= 4)g_enemy_image_type = 0;
        }
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
            A_check = true;//Aボタン押されたか
        }

        if (g_uicursorx == 3 && A_check == true) {
            Enemycheck = true; //敵停止
        }
    }


  //  DrawFormatString(0, 500, 0xffffff, "x = %d", g_enemyy / 30);
    SetDrawArea(115, 0, 1165, 600);
    if (Enemycheck == false) {
        DrawRotaGraph(115 + (g_enemyx + 15) - g_stage_x, g_enemyy + 30, 1.0, M_PI / 180 * 0, g_enemy_image[g_enemy_image_type], TRUE, g_Edirection);
    }
   SetDrawArea(0, 0, 1280, 720);
   A_check = false;//Aボタン押されたフラグを戻す
   if (time >= 3) {
       fps = 0;
       time = 0;
       Enemycheck = false;
       g_enemy_speed = 1;
   }
   
}
int HitBoxPlayer() {
        //x,yは中心座標とする
        int sx1 = g_playerx;
        int sy1 = g_playery;
        int sx2 = sx1 + 30;
        int sy2 = sy1 + 60;

        int dx1 = g_enemyx;
        int dy1 = g_enemyy;
        int dx2 = dx1 + 30;
        int dy2 = dy1 + 60;

        //短形が重なっていればあたり
        if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2 && Enemycheck == false) {
            return TRUE;
        }
        return FALSE;
}
void Enemy2()
{
    if (g_stage_scroll == FALSE) {
        if (Enemycheck1 == true) {
            g_enemy2_speed = 0;
            fps1++;
        }
        if (Enemycheck1 == true && fps1 % 60 == 0) {  //fps 60 で一秒
            time1++;
        }

        if (g_Edirection2 == FALSE && Enemycheck1 == false)
        {
            g_enemy2_hit_under_back = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 2][g_enemy2x / BLOCK_WIDTH];
            g_enemy2_hit_under_front = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 2][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
            g_enemy2_hit_lowerbody_front = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 1][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy2_hit_upperbody_front = MAP_DATA[g_enemy2y / BLOCK_WIDTH][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy2_hit_lowerbody_back = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 1][g_enemy2x / BLOCK_WIDTH];
            g_enemy2_hit_upperbody_back = MAP_DATA[g_enemy2y / BLOCK_WIDTH][g_enemy2x / BLOCK_WIDTH];
        }
        else if (g_Edirection2 == TRUE && Enemycheck1 == false)
        {
            g_enemy2_hit_under_back = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 2][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
            g_enemy2_hit_under_front = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 2][g_enemy2x / BLOCK_WIDTH];
            g_enemy2_hit_lowerbody_front = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 1][g_enemy2x / BLOCK_WIDTH];
            g_enemy2_hit_upperbody_front = MAP_DATA[g_enemy2y / BLOCK_WIDTH][g_enemy2x / BLOCK_WIDTH];
            g_enemy2_hit_lowerbody_back = MAP_DATA[(g_enemy2y / BLOCK_WIDTH) + 1][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
            g_enemy2_hit_upperbody_back = MAP_DATA[g_enemy2y / BLOCK_WIDTH][(g_enemy2x + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        }

        if (g_enemy2_hit_under_back > 0 && g_enemy2_hit_under_back < 10 && Enemycheck1 == false)
        {
            g_enemy2y = (g_enemy2y / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのy座標を整える

            if ((g_enemy2_hit_lowerbody_front == 0 || g_enemy2_hit_lowerbody_front >= g_block_quantity) && (g_enemy2_hit_upperbody_front == 0 || g_enemy2_hit_upperbody_front >= g_block_quantity))
            {
                if (g_Edirection2 == FALSE)g_enemy2x += g_enemy2_speed; //障害物に当たってなかったら進む
                else g_enemy2x -= g_enemy2_speed;
            }
            else
            {
                if (g_Edirection2 == FALSE)g_enemy2x = (g_enemy2x / BLOCK_WIDTH) * BLOCK_WIDTH, g_Edirection2 = TRUE; //プレイヤーがめり込んでるかもしれないからx座標を調整する
                else  g_enemy2x = ((g_enemy2x / BLOCK_WIDTH) + 1) * BLOCK_WIDTH, g_Edirection2 = FALSE;
            }
        }
        else if (Enemycheck1 == false)
        {
            if (g_direction == FALSE)g_enemy2x = (g_enemy2x / BLOCK_WIDTH) * BLOCK_WIDTH;  //キャラを穴の真ん中にする
            else g_enemy2x = ((g_enemy2x + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
            g_enemy2y += 5; //キャラを落とす
        }
        if (HitBoxPlayer2())
        {
            if (g_Edirection2 == FALSE)
            {
                g_Edirection2 = TRUE;
            }
            else
            {
                g_Edirection2 = FALSE;
            }
        }
        if ((g_enemy2x >= 68 * 30) && (g_Edirection2 == FALSE))g_Edirection2 = TRUE;//範囲指定
        if ((g_enemy2x <= 58 * 30) && (g_Edirection2 == TRUE))g_Edirection2 = FALSE;//範囲指定
        if ((g_enemy2y / BLOCK_WIDTH) + 1 < MAP_HIGHT)
        {
            ENEMY_MAP[g_enemy2y / BLOCK_WIDTH][g_enemy2x / BLOCK_WIDTH] = 1;
            ENEMY_MAP[(g_enemy2y / BLOCK_WIDTH) + 1][g_enemy2x / BLOCK_WIDTH] = 1;
            ENEMY_MAP[g_enemy2y / BLOCK_WIDTH][g_enemy2x / BLOCK_WIDTH + 1] = 2;
            ENEMY_MAP[(g_enemy2y / BLOCK_WIDTH) + 1][g_enemy2x / BLOCK_WIDTH + 1] = 2;
        }

        g_enemy2_time++;
        if (g_enemy2_time >= 8)
        {
            g_enemy2_image_type++;
            g_enemy2_time = 0;
            if (g_enemy2_image_type >= 4)g_enemy2_image_type = 0;
        }
        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) {
            A_check1 = true;//Aボタン押されたか
        }

        if (g_uicursorx == 3 && A_check1 == true) {
            Enemycheck1 = true; //敵停止
        }

    }
    //  DrawFormatString(0, 500, 0xffffff, "x = %d", g_enemy2y / 30);
    SetDrawArea(115, 0, 1165, 600);
    if (Enemycheck1 == false) {
        DrawRotaGraph(115 + (g_enemy2x + 15) - g_stage_x, g_enemy2y + 30, 1.0, M_PI / 180 * 0, g_enemy2_image[g_enemy2_image_type], TRUE, g_Edirection2);
    }
    SetDrawArea(0, 0, 1280, 720);
    A_check1 = false;//Aボタン押されたフラグを戻す
    if (time1 >= 3) {
        fps1 = 0;
        time1 = 0;
        Enemycheck1 = false;
        g_enemy2_speed = 1;
    }

}
int HitBoxPlayer2() {
    //x,yは中心座標とする
    int sx1 = g_playerx;
    int sy1 = g_playery;
    int sx2 = sx1 + 30;
    int sy2 = sy1 + 60;

    int dx1 = g_enemy2x;
    int dy1 = g_enemy2y;
    int dx2 = dx1 + 30;
    int dy2 = dy1 + 60;

    //短形が重なっていればあたり
    if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2 && Enemycheck1 == false) {
        return TRUE;
    }
    return FALSE;
}
/***********************************************
* 画像読み込み
***********************************************/
int LoadImages()
{
    //if ((g_player_image = LoadGraph("images/human.png")) == -1) return -1;
    if ((g_cursor_image = LoadGraph("images/kasoru.png")) == -1) return -1;
    if ((g_white_image = LoadGraph("images/white.png")) == -1) return -1;
    if ((ui.img_clockneedle = LoadGraph("images/clock needle.png")) == -1)return-1;
    if ((ui.img_clock = LoadGraph("images/clock2.png")) == -1)return-1;
    if ((ui.img_sun = LoadGraph("images/sun.png")) == -1)return-1;
    if ((ui.img_moon = LoadGraph("images/moon.png")) == -1)return-1;
    //if ((g_jump_image = LoadGraph("images/jump.png")) == -1) return -1;
    if ((g_haikei_image = LoadGraph("images/haikei.jpg")) == -1) return -1;
    if ((g_hammer = LoadGraph("images/hanma-.png")) == -1)return -1;

    if (LoadDivGraph("images/block/ddd.png", 12, 12, 1, 30, 30, g_block_image) == -1) return -1;
    if (LoadDivGraph("images/player/human.png", 4, 4, 1, 30, 60, g_player_image) == -1) return -1;
    if (LoadDivGraph("images/hone1.png", 4, 4, 1, 30, 60, g_enemy_image) == -1) return -1;
    if (LoadDivGraph("images/hone1.png", 4, 4, 1, 30, 60, g_enemy2_image) == -1) return -1;
    if (LoadDivGraph("images/item.png", 2, 2, 1, 30, 30, g_item_image) == -1) return -1;

}



