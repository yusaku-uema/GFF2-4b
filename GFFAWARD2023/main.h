#pragma once

enum ArrayImages { Character,EnemyImages }; //GetArrayImagesでの,type指定名前


int LoadImages(void); //画像読込み
int GetArrayImages(int type, int num); //使う画像指定