#pragma once

class Character
{
private:
	float x, y; //�����A�cy
	float speed; //���N�̈ړ����x
	bool moveflg; //�ړ��ۃt���O(�ǂɂԂ����Ă��Ȃ����Ȃǁj
	bool leftflg;//���Ɍ������Ă���̂����f�t���O
	int Move;    // �ړ����Ă��邩�ǂ����̃t���O( 0:��~��  1:�ړ��� )
	int MoveX, MoveY;// �e�����Ɉړ������
	int MoveCounter;// �ړ����n�߂Ă��牽�t���[���o�߂�������ێ�����ϐ�
public:
	Character(); //�R���X�g���N�^
	void DrawCharacter();  //�`��ƈړ�����
	float getCharacter_X(float); //���NX���W
	float getCharacter_Y(float); //���NY���W
	int getMove(); //�ړ��t���O�擾
	int getMoveX(); //�ړ��ʎ擾
	int getMoveY(); //�ړ��ʏ���
	~Character(); //�f�X�g���N�^
	
};


 
