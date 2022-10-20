#include"Enemy.h"
#include"main.h"

Enemy::Enemy() {
    timer = 0;
    g_enemy.x = 200;//810
    g_enemy.y = 480;
}

int Enemy::EnemyMove(void) {
    timer++;

    if (timer <= 200) {
        if (timer / 100 == 0) {
            g_enemy.x += 3;
        }
    }
    if (timer >= 200 && timer <= 290) {
        if (timer / 1000 == 0) {
            g_enemy.x += -3;
        }
    }
    else if (timer == 400) {
        timer = 0;
    }

    return 0;
}

void Enemy::EnemyDraw() {
    DrawGraph(g_enemy.x, g_enemy.y, GetArrayImages(EnemyImages,1), TRUE);
}