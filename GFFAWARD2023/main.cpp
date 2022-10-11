#include "DxLib.h"
#include"main.h"
#include"character.h"

int CharacterImages[16]; //���N�̃C���[�W�摜
int background1; //�w�i�摜
int blockImages; //�u���b�N�摜

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // �^�C�g��
    SetMainWindowText("�v���g�^�C�v��"); //�Q�[���^�C�g��
	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�ŋN��
	SetGraphMode(1280, 720, 0); //��ʃT�C�Y
    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������
	if (LoadImages() == -1)return -1; //�摜�Ǎ���
	
	SetDrawScreen(DX_SCREEN_BACK); // �`����ʂ𗠂ɂ���
    // �Q�[�����[�v
	while (ProcessMessage() == 0) {
        ClearDrawScreen();		// ��ʂ̏�����

		DrawGraph(0, 100, background1, FALSE); //�w�i���f

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

		
	}
		DxLib_End();	// DX���C�u�����g�p�̏I������

		return 0;
}


int LoadImages(void) { //�摜�Ǎ���
	if (LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90,CharacterImages) == 1)return -1; //���N��
	if((background1 = LoadGraph("images/background/street003_day.png")) == -1)return -1;// �w�i
	if ((blockImages = LoadGraph("images/block/0115_s1.png")) == -1)return -1; //�u���b�N
	
}

int GetArrayImages(int type, int num) { //type,�g�������摜�̗v�f�����w�肷�邱�ƂŁA�w�肵���摜���g����
	switch (type)
	{
	case Character: //���N
		if (0 <= num && num <= 16) {
			return CharacterImages[num];
		}
		else { return -1; }
		break;
	}
}