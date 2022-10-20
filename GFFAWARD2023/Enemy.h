#pragma once
#include"DxLib.h"

struct ENEMY {
	int flg;
	int type;
	int img;
	int x, y, w, h;
};

class Enemy {
public:
	int timer;
	struct ENEMY g_enemy;

	Enemy();
	int EnemyMove(void);
	void EnemyDraw(void);
};

extern Enemy enemy;