#include "DxLib.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // �^�C�g��
    SetMainWindowText("GFF");
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�ŋN��
	SetWindowSize(1280, 720); //��ʃT�C�Y
    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������
	
	SetDrawScreen(DX_SCREEN_BACK);// �`����ʂ𗠂ɂ���
    // �Q�[�����[�v
	while (ProcessMessage() == 0) {
        ClearDrawScreen();		// ��ʂ̏�����

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

		DxLib_End();	// DX���C�u�����g�p�̏I������

		return 0;
	}

}
