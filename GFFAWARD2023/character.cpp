#include"DxLib.h"
#include"character.h"



Character::Character() {
	x = 0;
	y = 0;
	speed = 0;
	leftflg = false;
	moveflg = false;
	MoveX = 0;
	MoveY = 0;
	MoveCounter = 0;
}

void Character::DrawCharacter() {
		
}

float Character::getCharacter_X() { //少年X座標
	return x;
}
float Character::getCharacter_Y() { //少年Y座標
	return y;
}

float Character::getMoveX() { //移動量取得
	return MoveX;
}
float Character::getMoveY() { //移動量所得
	return MoveY;
}