#pragma once

class Character
{
private:
	float x, y; //�����A�cy
	float speed; //���N�̈ړ����x
	bool moveflg; //�ړ��ۃt���O(�ǂɂԂ����Ă��Ȃ����Ȃǁj
	bool leftflg;//���Ɍ������Ă���̂����f�t���O
public:
	Character(); //�R���X�g���N�^
	void DrawCharacter();  //�`��ƈړ�����
	float getCharacter_X(float); //���NX���W
	float getCharacter_Y(float); //���NY���W
	~Character(); //�f�X�g���N�^
	
};


 
