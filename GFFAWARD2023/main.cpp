#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"

#define MAP_HIGHT 20
#define MAP_WIDTH 86

#define DRAW_MAP_HIGHT 20
#define DRAW_MAP_WIDTH 35

#define BLOCK_WIDTH 30
//#define PLAYER_HIGHT 30

/***********************************************
 * 変数
 ***********************************************/

int g_block_image[5];
int g_item_image[2];
int g_player_image[4];
int g_cursor_image;
int g_white_image;
//int g_jump_image;
int g_haikei_image;

int g_stage_count = 0;

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

<<<<<<< HEAD
int g_EnemyImage[4];

int g_enemy_hit_lowerbody_front = 0; //プレイヤーが当たった障害物
int g_enemy_hit_upperbody_front = 0;
int g_enemy_hit_lowerbody_back = 0; //プレイヤーが当たった障害物
int g_enemy_hit_upperbody_back = 0;
int g_enemy_hit_under_back = 1;
int g_enemy_hit_under_front = 1;
bool g_Edirection = true; //false = 右向き　true = 左向き
int g_enemy_image[4];
int g_enemyx = 6 * 120;
int g_enemyy = 7 * 70;
int g_enemy_hight = 60;
int g_enemy_width = 30;
int g_enemy_speed = 1;
int g_enemy_angle = 0;
int g_enemy_image_type = 0;
int g_enemyx_radius = 30 / 2;
int g_enemyy_radius = 60 / 2;
int g_enemy_time = 0;
=======
bool g_forcedtermination = false; // 強制終了

>>>>>>> 086bb6e6f291ce7edcb80049ba4d95d5c7f88f20
unsigned int MAP_DATA_INIT[MAP_HIGHT][MAP_WIDTH] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
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
void Sousa(void); // 操作
void Jump(void); //ジャンプ
void Walk(void);


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
        UI();

        ScreenFlip();         //裏画面の内容を表画面に反映

        if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_7){ //BACK押すと強制終了
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
    for (int i = 0; i < 3; i++)
    {
        DrawRotaGraph(490 + (150 * i), 660, 1.0, M_PI / 180 * 0, g_white_image, TRUE, FALSE);
       if(i == 1) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[0], TRUE, FALSE);
       if (i == 0) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_block_image[2], TRUE, FALSE);
       if (i == 2) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[1], TRUE, FALSE);

       if(i == g_uicursorx)DrawRotaGraph(490 + (150 * i), 660, 3.3, M_PI / 180 * 0, g_cursor_image, TRUE, FALSE);
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
                if (MAP_DATA[i][j] < 10)DrawGraph(115 + (30 * j) - g_stage_x, 30 * i, g_block_image[MAP_DATA[i][j]], TRUE);
                else DrawGraph(115 + (30 * j) - g_stage_x, 30 * i, g_item_image[MAP_DATA[i][j] - 10], TRUE);
            }
            DrawGraph(115 + (30 * g_cursorx), 30 * g_cursory, g_cursor_image, TRUE);

            


            //DrawFormatString(14 * j, 14 * i, 0xffffff, "%d", MAP_DATA[i][j]);
            //DrawLine(0, 30 * i, MAP_WIDTH * 30, 30 * i, 0xffffff, TRUE);
            //DrawLine(30 * j, 0, 30 * j, MAP_HIGHT * 30, 0xffffff, TRUE);
            PLAYER_MAP[i][j] = 0;
        }
    }


    SetDrawArea(0, 0, 1280, 720);

    if (g_stage_scroll == TRUE)
    {
        g_stage_x += 10;

        if (g_stage_x > ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH))
        {
            g_stage_scroll = FALSE;
            g_stage_x = ((DRAW_MAP_WIDTH - 1) * BLOCK_WIDTH);
            g_stage_count++;
            //g_cursorx = g_cursorx + 35;
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
                if(g_uicursorx == 1 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] > 0 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] < 10) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 10;
                if (g_uicursorx == 0 && MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 0) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 2;
            }

            if (g_uicursorx == 2 && (MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 2 || MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 10)) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 0;

            //else if (MAP_DATA[g_cursory][g_cursorx] != 0)MAP_DATA[g_cursory][g_cursorx] = 0;
        }
        g_AKey = TRUE;
    }

    if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5)
    {
        if (g_uicursor == FALSE)
        {
            if (g_uicursorx > 0)g_uicursorx--;
            else g_uicursorx = 2;
            g_uicursor = TRUE;
        }
    }
    else if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)
    {
        if (g_uicursor == FALSE)
        {
            if (g_uicursorx < 2)g_uicursorx++;
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
        if ((g_player_hit_lowerbody_back == 10) || g_jump > 0)Jump();
        else Walk();

        if (115 + (g_playerx + 15) - g_stage_x >= 1155)
        {
            g_stage_scroll = TRUE;
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;
            else ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH)* BLOCK_WIDTH;
        }

        if ((g_playery / BLOCK_WIDTH) + 1 < MAP_HIGHT)
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

    DrawFormatString(0, 500, 0xffffff, "x = %d", g_playery / 30);
    DrawRotaGraph(115 + (g_playerx + 15) - g_stage_x, g_playery + 30, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_direction);
}

void Walk(void)
{
    if (g_player_hit_under_back > 0 && g_player_hit_under_back < 10)
    {
        g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのy座標を整える

        if ((g_player_hit_lowerbody_front == 0 || g_player_hit_lowerbody_front >= 10) && (g_player_hit_upperbody_front == 0 || g_player_hit_upperbody_front >= 10))
        {
            if (g_direction == FALSE)g_playerx += g_player_speed; //障害物に当たってなかったら進む
            else g_playerx -= g_player_speed;
        }
        else
        {
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH, g_direction = TRUE; //プレイヤーがめり込んでるかもしれないからx座標を調整する
            else  g_playerx = ((g_playerx / BLOCK_WIDTH) + 1) * BLOCK_WIDTH, g_direction = FALSE;
        }
    }
    else
    {
        if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;  //キャラを穴の真ん中にする
        else g_playerx = ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
        g_playery += 5; //キャラを落とす
    }
    
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

        if (g_jump_angle >= 270 || g_jump_angle <= -90) //ジャンプして、落ち始めたら
        {
            if (g_player_hit_under_front > 0 && g_player_hit_under_front < 10)
            {
                g_jump = 2;
                g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのｙ座標を整える
            }
            else if (g_jump_angle >= 360 || g_jump_angle <= -180) //ブロックなどに当たらなかったら
            {
                g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //y座標を整える
                g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH; //x座標を整える
                g_jump = 0;
            }
        }
        if (g_player_hit_lowerbody_back > 0 && g_player_hit_lowerbody_back < 10)
        {
            if (g_direction == FALSE)g_playerx = g_playerx / BLOCK_WIDTH * BLOCK_WIDTH;
            else g_playerx = (g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH * BLOCK_WIDTH;
            g_jump = 0;
        }
        break;

    case 2:

        if (g_direction == FALSE)g_playerx += g_player_speed;
        else g_playerx -= g_player_speed;

        if (g_player_hit_under_back > 0 && g_player_hit_under_back < 10)
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
    if (g_Edirection == FALSE)
    {
        g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
        g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
    }
    else
    {
        g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//足元が穴じゃなければ
        g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
    }

        if (g_enemy_hit_under_back > 0 && g_enemy_hit_under_back < 10)
        {
            g_enemyy = (g_enemyy / BLOCK_WIDTH) * BLOCK_WIDTH; //プレイヤーのy座標を整える

            if ((g_enemy_hit_lowerbody_front == 0 || g_enemy_hit_lowerbody_front >= 10) && (g_enemy_hit_upperbody_front == 0 || g_enemy_hit_upperbody_front >= 10))
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
        else
        {
            if (g_Edirection == FALSE)g_enemyx = (g_enemyx / BLOCK_WIDTH) * BLOCK_WIDTH;  //キャラを穴の真ん中にする
            else g_enemyx = ((g_enemyx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
            g_enemyy += 5; //キャラを落とす
        }


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

    DrawFormatString(0, 500, 0xffffff, "x = %d", g_enemyy / 30);
    DrawRotaGraph(115 + (g_enemyx + 15) - g_stage_x, g_enemyy + 30, 1.0, M_PI / 180 * 0, g_enemy_image[g_enemy_image_type], TRUE, g_Edirection);
}

/***********************************************
* 画像読み込み
***********************************************/
int LoadImages()
{
    //if ((g_player_image = LoadGraph("images/human.png")) == -1) return -1;
    if ((g_cursor_image = LoadGraph("images/cursor mini.png")) == -1) return -1;
    if ((g_white_image = LoadGraph("images/white.png")) == -1) return -1;
    //if ((g_jump_image = LoadGraph("images/jump.png")) == -1) return -1;
    if ((g_haikei_image = LoadGraph("images/haikei.jpg")) == -1) return -1;

    if (LoadDivGraph("images/block/stage3.png", 5, 5, 1, 30, 30, g_block_image) == -1) return -1;
    if (LoadDivGraph("images/player/human.png", 4, 4, 1, 30, 60, g_player_image) == -1) return -1;
    if (LoadDivGraph("images/hone.png", 4, 4, 1, 30, 60, g_enemy_image) == -1) return -1;
    if (LoadDivGraph("images/item.png", 2, 2, 1, 30, 30, g_item_image) == -1) return -1;

}



