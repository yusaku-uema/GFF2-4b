#pragma once

class Character
{
private:
	float x, y; //�����A�cy
	float speed; //���N�̈ړ����x
	bool moveflg; //�ړ��ۃt���O(�ǂɂԂ����Ă��Ȃ����Ȃǁj
	bool leftflg;//���Ɍ������Ă���̂����f�t���O
	float MoveX, MoveY;// �e�����Ɉړ������
	int MoveCounter;// �ړ����n�߂Ă��牽�t���[���o�߂�������ێ�����ϐ�
	int Move; //�ړ���
public:
	Character(); //�R���X�g���N�^
	void DrawCharacter();  //�`��ƈړ�����
	float getCharacter_X(); //���NX���W
	float getCharacter_Y(); //���NY���W
	float getMoveX(); //�ړ��ʎ擾
	float getMoveY(); //�ړ��ʏ���
	//~Character(); //�f�X�g���N�^
	
};


 
