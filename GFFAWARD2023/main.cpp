#include <algorithm> // std::max���g�p���邽��
#define NOMINMAX
#include "DxLib.h"

//
// �����蔻����s���֐�
// 
// �΂̃L���� ��   x1
// �@�@�@�@�@ ��   y1
// �@�@�@�@�@ ���� w1
// �@�@�@�@�@ �c�� h1
// ���̃L���� ��   x2
// �@�@�@�@�@ ��   y2
// �@�@�@�@�@ ���� w2
// �@�@�@�@�@ �c�� h2
//
int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int L1 = x1;      // ��
	int R1 = x1 + w1; // �E(��+����)
	int L2 = x2;      // ��
	int R2 = x2 + w2; // �E(��+����)

	if (R1 <= L2) return 0; //< �����������Ȃ����Ƃɂ���
	if (R2 <= L1) return 0; //< �����������Ȃ����Ƃɂ���

	int U1 = y1;      // ��
	int D1 = y1 + h1; // ��(��+�c��)
	int U2 = y2;      // ��
	int D2 = y2 + h2; // ��(��+�c��)

	if (D1 <= U2) return 0; //< �����������Ȃ����Ƃɂ���
	if (D2 <= U1) return 0; //< �����������Ȃ����Ƃɂ���

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	//======================================================
	// �E�C���h�E�ݒ��DX���C�u�����̏�����
	//======================================================
	const int SCREEN_WIDTH = 640;		//< �X�N���[�����̑傫��
	const int SCREEN_HEIGHT = 480;		//< �X�N���[���c�̑傫��

	// Windows���[�h�ɂ���
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	// DX���C�u����������
	if (DxLib_Init() == -1)
	{
		//�������Ɏ��s
		return -1;
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	//======================================================
	// �Q�[������
	//======================================================
	//------------------------------------------------------
	// �Q�[������������
	//------------------------------------------------------
	const int CHARA_WIDTH = 32;
	const int CHARA_HEIGHT = 32;

	float x = (SCREEN_WIDTH - CHARA_WIDTH) / 2;	//< ��ʂ̒��S
	float y = (SCREEN_HEIGHT - CHARA_HEIGHT) / 2;	//< ��ʂ̒��S

	float yadd = 0.0f;

	int chara_act[16];
	LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90, chara_act);

	int act_motion[] = { 0, 1, 2, 1, };
	int act_index = 0;

	int MAX_MOTION_INDEX = 4; //< 0,1,2,1 ��4��� [0�`3]�܂łɂ��邽�߂ɗp��

	const int ACT_SPEED = 20;
	int act_wait = ACT_SPEED;

	const int ACT_DIR_SLIDE = 3; //< ���̃L�������X���C�h������Ύ��̗��I������
	int act_dir = 0;

	// �}�b�v�`�b�v���[�h
	const int SIZE_MAP_X = 32;  //< �}�b�v�`�b�vX�T�C�Y
	const int SIZE_MAP_Y = 32;	//< �}�b�v�`�b�vY�T�C�Y
	const int NUM_CHIP_X = 10;  //< ��10���
	const int NUM_CHIP_Y = 4;   //< �c4���
	const int NUM_CHIP_ALL = NUM_CHIP_X * NUM_CHIP_Y; //< 40��
	int chip[NUM_CHIP_ALL];
	LoadDivGraph("mapchip.png", NUM_CHIP_ALL,
		NUM_CHIP_X, NUM_CHIP_Y,
		SIZE_MAP_X, SIZE_MAP_Y,
		chip);

	// �}�b�v�`�b�v���g�����w�i
	const int NUM_MAP_X = 20; // 32x20=640
	const int NUM_MAP_Y = 15; // 32x15=480
	int data[] = {
		// ��20x15
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,

		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,

		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0,  0,   0,  0,  0,  0, 10,
		10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,  10, 10, 10, 10, 10,
	};

	//------------------------------------------------------
	// ���C�����[�v����
	//------------------------------------------------------
	while (ProcessMessage() == 0)
	{
		//����ʏ���
		ClearDrawScreen();

		// �w�i
		for (int j = 0; j < NUM_MAP_Y; j++)
		{
			for (int i = 0; i < NUM_MAP_X; i++)
			{
				int no = data[i + j * NUM_MAP_X];
				if (no != 0)
				{
					DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, chip[no], FALSE);
				}
			}
		}

		// �O��̈ʒu���o���Ă���
		float old_x = x;
		float old_y = y;
		float speed = 3.0f;

		// �L�[�����擾����
		int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		// �L�[�ňړ�������
		if (input & PAD_INPUT_RIGHT)
		{
			x += speed;
			act_dir = 2; //< 2��ڂ�I��(0�X�^�[�g)
		}
		if (input & PAD_INPUT_LEFT)
		{
			x -= speed;
			act_dir = 1; //< 1��ڂ�I��(0�X�^�[�g)
		}
		if (input & PAD_INPUT_A) //< �L�[�{�[�h�Ȃ��Z�{�^�� 
		{
			yadd = -5.0f;
		}
		y += yadd;
		yadd += 0.2f;
		if (yadd > 30) yadd = 30; //< �}�X��΂��Ȃ��悤�ɐ���

		// �u���b�N�̓����蔻��
		for (int j = 0; j < NUM_MAP_Y; j++)
		{
			for (int i = 0; i < NUM_MAP_X; i++)
			{
				int no = data[i + j * NUM_MAP_X];
				if (no >= 10 && no < 20)
				{
					if (CheckHit(i * SIZE_MAP_X, j * SIZE_MAP_Y, SIZE_MAP_X, SIZE_MAP_Y,
						x, y, CHARA_WIDTH, CHARA_HEIGHT))
					{
						// �㉺���瓖�����Ă���
						if (y != old_y)
						{
							int _y = std::max(y, old_y);
							_y /= SIZE_MAP_Y;
							_y *= SIZE_MAP_Y;
							y = _y;
							yadd = 0.0f;
						}
						else
							// ���E���瓖�����Ă���
							if (x != old_x)
							{
								int _x = std::max(x, old_x);
								_x /= SIZE_MAP_X;
								_x *= SIZE_MAP_X;
								x = _x;
							}
					}
				}
			}
		}

		if (--act_wait <= 0)
		{
			act_index++;
			act_wait = ACT_SPEED;
			act_index %= MAX_MOTION_INDEX;
		}

		int motion_index = act_motion[act_index];

		// �����̃L������\������
		DrawGraph(x, y, chara_act[motion_index + act_dir * ACT_DIR_SLIDE], TRUE);

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();
	}

	//======================================================
	// DX���C�u�����I���ƃv���O�����I��
	//======================================================
	DxLib_End();
	return 0;
}
