#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"stdlib.h"
#include"SceneManager.h"
#include"Title.h"
#include"GameMain.h"

/***********************************************
 * �v���O�����J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetMainWindowText("�Q�[��");  //�^�C�g����ݒ�

    SetGraphMode(1280, 720, 16);
    ChangeWindowMode(TRUE);		               // �E�B���h�E���[�h�ŋN��

    if (DxLib_Init() == -1) return -1;	   // DX���C�u�����̏���������
    SceneManager* sceneMng;
    SetDrawScreen(DX_SCREEN_BACK);	           // �`����ʂ𗠂ɂ���
    try
    {
        sceneMng = new SceneManager((AbstractScene*)new Title());

    }
    catch (const char* err)
    {
        OutputDebugString(err);
        return 0;
    }
    while (ProcessMessage() == 0 && sceneMng->Update() != nullptr)
    {
        ClearDrawScreen();  //��ʂ̏�����
        sceneMng->Draw();
        ScreenFlip();         //����ʂ̓��e��\��ʂɔ��f
    }

    DxLib_End();  //DX���C�u�����g�p�̏I������
    return 0;  //�\�t�g�̏I��
}

