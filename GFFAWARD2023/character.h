#pragma once

class Character
{
private:
	float x, y; //�����A�cy
	float speed; //���N�̈ړ����x
	bool moveflg; //�ړ��ۃt���O(�ǂɂԂ����Ă��Ȃ����Ȃǁj
	bool leftflg;//���Ɍ������Ă���̂����f�t���O
	int MoveX, MoveY;// �e�����Ɉړ������
	int MoveCounter;// �ړ����n�߂Ă��牽�t���[���o�߂�������ێ�����ϐ�
public:
	Character(); //�R���X�g���N�^
	void DrawCharacter();  //�`��ƈړ�����
	//float getCharacter_X(); //���NX���W
	//float getCharacter_Y(); //���NY���W
	int getMoveX(); //�ړ��ʎ擾
	int getMoveY(); //�ړ��ʏ���
	~Character(); //�f�X�g���N�^
	
};

float getCharacter_X(); //���NX���W
float getCharacter_Y(); //���NY���W
//Character character;


 
