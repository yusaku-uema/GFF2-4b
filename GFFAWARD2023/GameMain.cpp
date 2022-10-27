#include"DxLib.h"
#include"GameMain.h"

GameMain::GameMain()
{
   /* PLAYER_MAP[g_map_i][g_map_j] = 0;*/
    if ((g_cursor_image = LoadGraph("images/cursor mini.png")) == -1);
    if ((g_white_image = LoadGraph("images/white.png")) == -1);
    if ((g_haikei_image = LoadGraph("images/haikei.jpg")) == -1);
    if (LoadDivGraph("images/block/ddd.png", 12, 12, 1, 30, 30, g_block_image) == -1) ;
    if (LoadDivGraph("images/player/human.png", 4, 4, 1, 30, 60, g_player_image) == -1);
    if (LoadDivGraph("images/hone1.png", 4, 4, 1, 30, 60, g_enemy_image) == -1) ;
    if (LoadDivGraph("images/item.png", 2, 2, 1, 30, 30, g_item_image) == -1);

    Init();
}


AbstractScene* GameMain::Update()
{
    Scroll();
    Sousa();
    Player();
    Enemy();
	return this;
}

void GameMain::Draw() const
{
    Stage();
    UI();
    PlayerDraw();
    EnemyDraw();
}


void GameMain::Init()
{
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
}

/***********************************************
* UI
***********************************************/
void GameMain::UI(void)const
{
    for (int i = 0; i < 3; i++)
    {
        DrawRotaGraph(490 + (150 * i), 660, 1.0, M_PI / 180 * 0, g_white_image, TRUE, FALSE);
        if (i == 1) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[0], TRUE, FALSE);
        if (i == 0) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_block_image[1], TRUE, FALSE);
        if (i == 2) DrawRotaGraph(490 + (150 * i), 660, 3.0, M_PI / 180 * 0, g_item_image[1], TRUE, FALSE);

        if (i == g_uicursorx)DrawRotaGraph(490 + (150 * i), 660, 3.3, M_PI / 180 * 0, g_cursor_image, TRUE, FALSE);
    }
}

/***********************************************
* �X�e�[�W�`��
***********************************************/
void GameMain::Stage()const
{
    SetDrawArea(115, 0, 1165, 600);

    DrawGraph(0 - (g_stage_x / 5), 0, g_haikei_image, FALSE);

    for (int g_map_i = 0; g_map_i < MAP_HIGHT; g_map_i++)
    {
        for (int g_map_j = 0; g_map_j < MAP_WIDTH; g_map_j++)
        {


            if (MAP_DATA[g_map_i][g_map_j] != 0)
            {
                if (MAP_DATA[g_map_i][g_map_j] <= g_block_quantity)DrawGraph(115 + (30 * g_map_j) - g_stage_x, 30 * g_map_i, g_block_image[MAP_DATA[g_map_i][g_map_j]], TRUE);
                else DrawGraph(115 + (BLOCK_WIDTH * g_map_j) - g_stage_x, BLOCK_WIDTH * g_map_i, g_item_image[MAP_DATA[g_map_i][g_map_j] - (g_block_quantity + 1)], TRUE);
            }
            DrawGraph(115 + (30 * g_cursorx), 30 * g_cursory, g_cursor_image, TRUE);




            //DrawFormatString(14 * j, 14 * i, 0xffffff, "%d", MAP_DATA[i][j]);
            //DrawLine(0, 30 * i, MAP_WIDTH * 30, 30 * i, 0xffffff, TRUE);
            //DrawLine(30 * j, 0, 30 * j, MAP_HIGHT * 30, 0xffffff, TRUE);
        }
    }
    SetDrawArea(0, 0, 1280, 720);

}

void GameMain::Scroll(void)
{
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
            }
        }
    }
}

void GameMain::Sousa(void)
{
    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) &&
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) &&
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) &&
        !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN))g_old_key = 0;

    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A))g_AKey = FALSE;

    if (!(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_5) && !(GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_6)) g_uicursor = FALSE;

    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) ||
        (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) ||
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
                if (g_uicursorx == 1 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] > 0 && MAP_DATA[g_cursory + 1][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] <= g_block_quantity) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = g_block_quantity + 1; //�g�����|������ǉ�
                if (g_uicursorx == 0 && MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 0) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 2; //�u���b�N��ǉ�
            }

            if (g_uicursorx == 2 && (MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == 2 || MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] == g_block_quantity + 1)) MAP_DATA[g_cursory][g_cursorx + ((DRAW_MAP_WIDTH - 1) * g_stage_count)] = 0; // �����S���̏���

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
    for (int i = 0; i < MAP_HIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            PLAYER_MAP[i][j] = 0;
        }
    }
    PLAYER_MAP[g_playery / 30][g_playerx / 30] = 1;
    PLAYER_MAP[(g_playery / 30) + 1][g_playerx / 30] = 1;
}

void GameMain::Player()
{
    if (g_direction == FALSE)
    {
        g_player_hit_under_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][g_playerx / BLOCK_WIDTH];
        g_player_hit_under_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//������������Ȃ����
        g_player_hit_lowerbody_front = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_player_hit_upperbody_front = MAP_DATA[g_playery / BLOCK_WIDTH][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_player_hit_lowerbody_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 1][g_playerx / BLOCK_WIDTH];
        g_player_hit_upperbody_back = MAP_DATA[g_playery / BLOCK_WIDTH][g_playerx / BLOCK_WIDTH];
    }
    else
    {
        g_player_hit_under_back = MAP_DATA[(g_playery / BLOCK_WIDTH) + 2][(g_playerx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//������������Ȃ����
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
}
void GameMain::PlayerDraw()const
{
    DrawFormatString(0, 500, 0xffffff, "x = %d", g_playery / 30);
    DrawRotaGraph(115 + (g_playerx + 15) - g_stage_x, g_playery + 30, 1.0, M_PI / 180 * 0, g_player_image[g_player_image_type], TRUE, g_direction);
}
void GameMain::Walk(void)
{
    if (g_player_hit_under_back > 0 && g_player_hit_under_back <= g_block_quantity)
    {
        g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //�v���C���[��y���W�𐮂���

        if ((g_player_hit_lowerbody_front == 0 || g_player_hit_lowerbody_front > g_block_quantity) && (g_player_hit_upperbody_front == 0 || g_player_hit_upperbody_front > g_block_quantity))
        {
            if (g_direction == FALSE)g_playerx += g_player_speed; //��Q���ɓ������ĂȂ�������i��
            else g_playerx -= g_player_speed;
        }
        else
        {
            if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH, g_direction = TRUE; //�v���C���[�̃u���b�N�̓����蔻��P����X
            else  g_playerx = ((g_playerx / BLOCK_WIDTH) + 1) * BLOCK_WIDTH, g_direction = FALSE;
        }
    }
    else
    {
        if (g_direction == FALSE)g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH;  //�L���������̐^�񒆂ɂ���
        else g_playerx = ((g_playerx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
        g_playery += 5; //�L�����𗎂Ƃ�
    }
    if (HitBoxPlayer())
    {
        if (g_direction == FALSE)
        {
            g_direction = TRUE;
        }
        else
        {
            g_direction = FALSE;
        }
    }
}

void GameMain::Jump(void)
{
    switch (g_jump)
    {
    case 0:
        g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH; //x���W�𐮂���
        g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //y���W�𐮂���
        g_jump_centery = g_playery; //�~��`���ăW�����v���邽�߂̒��S���Wy��ݒ�
        if (g_direction == FALSE)g_jump_centerx = g_playerx + (BLOCK_WIDTH / 2), g_jump_angle = 180; //���S���W���ƃW�����v���邽�߂̌��݂̊p�x��ݒ�
        else g_jump_centerx = g_playerx - (BLOCK_WIDTH / 2), g_jump_angle = 0; //���S���W���ƃW�����v���邽�߂̌��݂̊p�x��ݒ�
        g_jump = 1;
        break;

    case 1:
        if (g_direction == FALSE) g_jump_angle += 4; //�~��`�����߂̃A���O�������Z
        else g_jump_angle -= 4; ////�~��`�����߂̃A���O�������Z

        g_playery = (sin(g_jump_angle * M_PI / 180) * 90) + g_jump_centery; //�~��`�����߂�y���W���v�Z
        g_playerx = (cos(g_jump_angle * M_PI / 180) * 15) + g_jump_centerx; //�~��`�����߂�x���W���v�Z

        if (g_jump_angle >= 270 || g_jump_angle <= -90) //�W�����v���āA�����n�߂���
        {
            if (g_player_hit_under_front > 0 && g_player_hit_under_front <= g_block_quantity)
            {
                g_jump = 2;
                g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //�v���C���[�̂����W�𐮂���
            }
            else if (g_jump_angle >= 360 || g_jump_angle <= -180) //�u���b�N�Ȃǂɓ�����Ȃ�������
            {
                g_playery = (g_playery / BLOCK_WIDTH) * BLOCK_WIDTH; //y���W�𐮂���
                g_playerx = (g_playerx / BLOCK_WIDTH) * BLOCK_WIDTH; //x���W�𐮂���
                g_jump = 0;
            }
        }
        if (g_player_hit_upperbody_back > 0 && g_player_hit_upperbody_back <= g_block_quantity)
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

    //DrawFormatString(300, 300, 0xffffff, "%d �A���O��", g_jump_endy);
}
void GameMain::Enemy()
{
    if (g_Edirection == FALSE)
    {
        g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//������������Ȃ����
        g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
    }
    else
    {
        g_enemy_hit_under_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];//������������Ȃ����
        g_enemy_hit_under_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 2][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_front = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_upperbody_front = MAP_DATA[g_enemyy / BLOCK_WIDTH][g_enemyx / BLOCK_WIDTH];
        g_enemy_hit_lowerbody_back = MAP_DATA[(g_enemyy / BLOCK_WIDTH) + 1][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
        g_enemy_hit_upperbody_back = MAP_DATA[g_enemyy / BLOCK_WIDTH][(g_enemyx + (BLOCK_WIDTH - 1)) / BLOCK_WIDTH];
    }

    if (g_enemy_hit_under_back > 0 && g_enemy_hit_under_back < 10)
    {
        g_enemyy = (g_enemyy / BLOCK_WIDTH) * BLOCK_WIDTH; //�v���C���[��y���W�𐮂���

        if ((g_enemy_hit_lowerbody_front == 0 || g_enemy_hit_lowerbody_front >= g_block_quantity) && (g_enemy_hit_upperbody_front == 0 || g_enemy_hit_upperbody_front >= g_block_quantity))
        {
            if (g_Edirection == FALSE)g_enemyx += g_enemy_speed; //��Q���ɓ������ĂȂ�������i��
            else g_enemyx -= g_enemy_speed;
        }
        else
        {
            if (g_Edirection == FALSE)g_enemyx = (g_enemyx / BLOCK_WIDTH) * BLOCK_WIDTH, g_Edirection = TRUE; //�v���C���[���߂荞��ł邩������Ȃ�����x���W�𒲐�����
            else  g_enemyx = ((g_enemyx / BLOCK_WIDTH) + 1) * BLOCK_WIDTH, g_Edirection = FALSE;
        }
    }
    else
    {
        if (g_direction == FALSE)g_enemyx = (g_enemyx / BLOCK_WIDTH) * BLOCK_WIDTH;  //�L���������̐^�񒆂ɂ���
        else g_enemyx = ((g_enemyx + BLOCK_WIDTH - 1) / BLOCK_WIDTH) * BLOCK_WIDTH;
        g_enemyy += 5; //�L�����𗎂Ƃ�
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

}
void GameMain::EnemyDraw()const
{
    DrawRotaGraph(115 + (g_enemyx + 15) - g_stage_x, g_enemyy + 30, 1.0, M_PI / 180 * 0, g_enemy_image[g_enemy_image_type], TRUE, g_Edirection);
}

int GameMain::HitBoxPlayer() {
    //x,y�͒��S���W�Ƃ���
    int sx1 = g_playerx;
    int sy1 = g_playery;
    int sx2 = sx1 + 30;
    int sy2 = sy1 + 60;

    int dx1 = g_enemyx;
    int dy1 = g_enemyy;
    int dx2 = dx1 + 30;
    int dy2 = dy1 + 60;

    //�Z�`���d�Ȃ��Ă���΂�����
    if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
        return TRUE;
    }
    return FALSE;
}
