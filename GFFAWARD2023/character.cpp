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

float Character::getCharacter_X() { //���NX���W
	return x;
}
float Character::getCharacter_Y() { //���NY���W
	return y;
}

float Character::getMoveX() { //�ړ��ʎ擾
	return MoveX;
}
float Character::getMoveY() { //�ړ��ʏ���
	return MoveY;
}