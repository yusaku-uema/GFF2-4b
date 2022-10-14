#pragma once
#include"DxLib.h"

struct ENEMY {
	int flg;
	int type;
	int img;
	int x, y, w, h;
};

struct ENEMY g_enemy;

class Enemy {
public:
	int timer;

	Enemy();
	int EnemyMove(void);
};