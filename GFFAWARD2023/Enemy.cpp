#include"Enemy.h"

int img_Enemy;
int timer;



int Enemy::EnemyMove(void) {
    timer++;
    /*DrawGraph(g_enemy.x, 150, img_Enemy, TRUE);*/

    if (timer <= 200) {
        if (timer / 100 == 0) {
            g_enemy.x += 5;
        }
    }
    if (timer >= 200 && timer <= 290) {
        if (timer / 1000 == 0) {
            g_enemy.x += -5;
        }
    }
    else if (timer == 400) {
        timer = 0;
    }

    return 0;
}