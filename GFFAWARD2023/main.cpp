#include"DxLib.h"
#include"main.h"
#include"character.h"
#include"map.h"

#define MAP_NUM 1 //�}�b�v�̐�

#define MAP_SIZE 32 //�}�b�v�`�b�v�[�̃h�b�g

#define MAP_WIDTH_MAX 40 //�}�b�v�̍ő剡��
#define MAP_HEIGHT_MAX 40 //�}�b�v�̍ő�c����

#define MOVE_FRAME 15 //�ړ��ɂ�����t���[����

int CharacterImages[16]; //���N�̃C���[�W�摜
int background1; //�w�i�摜
int blockImages; //�u���b�N�摜
int MapNo; //�}�b�v�̐�
int Key; //�L�[����
int ScrollX, ScrollY;
int MoveX, MoveY;
int Move;
int PlayerY, PlayerX;
int MoveCounter;

Character character;

#define MAP_NUM 1 //�}�b�v�̐�

#define MAP_SIZE 32 //�}�b�v�`�b�v�[�̃h�b�g

#define MAP_WIDTH_MAX 40 //�}�b�v�̍ő剡��
#define MAP_HEIGHT_MAX 40 //�}�b�v�̍ő�c����

#define MOVE_FRAME 15 //�ړ��ɂ�����t���[����

void GraphDraw(int ScrollX, int ScrollY);


// �}�b�v�̍\����
struct MAPDATA
{
    // �}�b�v�̕�
    int Width;

    // �}�b�v�̍���
    int Height;

    // �}�b�v
    int Data[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
};

// �}�b�v�̃f�[�^
MAPDATA MapData[MAP_NUM] =
{
    // �}�b�v�O
    {
        40,
        32,
        {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 1, 0, 0 } ,
            { 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 1, 0, 0, 0, 1, 0, 0 } ,
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 1, 0, 0, 0, 1, 0, 0 } ,
            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 0, 0, 0, 1, 1, 1, 0, 0 } ,

            { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 1, 0, 0, 0, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 0, 1, 1, 0, 0 } ,
            { 0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 0, 1, 0, 1, 1, 1, 0, 0, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  1, 1, 1, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 1, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 1, 1, 1, 0, 0, 1, 1, 0 } ,
            { 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  0, 0, 0, 1, 0, 1, 1, 1, 1, 0 } ,

            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 0, 1, 0, 1, 0, 0, 0, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 1 ,  1, 1, 0, 1, 0, 1, 0, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 1, 1, 1, 0, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 0, 0, 0, 0, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,  1, 1, 1, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 0, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 0, 1, 0 } ,

            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 1, 0, 1, 0 } ,
            { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 0, 0, 0, 0 ,  0, 0, 0, 0, 1, 1, 1, 0, 1, 1 ,  1, 1, 1, 1, 1, 1, 1, 0, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 1, 1, 1, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 1, 1, 0, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 1, 0 } ,
            { 0, 1, 1, 0, 0, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 1, 1, 1, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 0, 0, 0, 1, 0, 0, 1, 0 ,  0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 1, 1, 1, 1, 1, 1, 0, 0, 0 ,  0, 1, 1, 1, 1, 1, 0, 0, 1, 1 ,  1, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,  1, 1, 1, 1, 1, 1, 1, 1, 1, 0 } ,
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } ,
        }
    },
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // �^�C�g��
    SetMainWindowText("�v���g�^�C�v��"); //�Q�[���^�C�g��
	SetOutApplicationLogValidFlag(FALSE);   //���O�o�͂𖳌��ɂ���
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�ŋN��
	SetGraphMode(1280, 720, 0); //��ʃT�C�Y
    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������
	if (LoadImages() == -1)return -1; //�摜�Ǎ���
	

    // �`����ʂ𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �v���C���[�̏����ʒu���Z�b�g
    PlayerX = 1;
    PlayerY = 1;

    // �ŏ��͒�~��(0)�ɂ��Ă���
    Move = 0;

    // ���[�v
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ�������
        ClearDrawScreen();

        
        // �ړ����ł͂Ȃ��ꍇ�L�[���͂��󂯕t����
        if (Move == 0)
        {
            // �L�[���͂𓾂�
            Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

            // �L�[���͂ɉ����ăv���C���[�̍��W���ړ�
            if (Key & PAD_INPUT_LEFT)
            {
                Move = 1;
                MoveX = -1;
                MoveY = 0;
            }
            if (Key & PAD_INPUT_RIGHT)
            {
                Move = 1;
                MoveX = 1;
                MoveY = 0;
            }
            if (Key & PAD_INPUT_UP)
            {
                Move = 1;
                MoveX = 0;
                MoveY = -1;
            }
            if (Key & PAD_INPUT_DOWN)
            {
                Move = 1;
                MoveX = 0;
                MoveY = 1;
            }

            // �i���s�\�ȃ}�b�v�������ꍇ�͈ړ��ł��Ȃ�
            if (Move == 1)
            {
                if (MapData[MapNo].Data[PlayerY + MoveY][PlayerX + MoveX] == 0)
                {
                    Move = 0;
                }
                else
                {
                    MoveCounter = 0;
                }
            }

            // ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
            ScrollX = 0;
            ScrollY = 0;
        }

        // �ړ����̏ꍇ�͈ړ��������s��
        if (Move == 1)
        {
            MoveCounter++;

            // �ړ��������I���������~���ɂ���
            if (MoveCounter == MOVE_FRAME)
            {
                Move = 0;

                // �v���C���[�̈ʒu��ύX����
                PlayerX += MoveX;
                PlayerY += MoveY;

                // ��~���͉�ʂ̃X�N���[���͍s��Ȃ�
                ScrollX = 0;
                ScrollY = 0;
            }
            else
            {
                // �o�ߎ��Ԃ���X�N���[���ʂ��Z�o����
                ScrollX = -(MoveX * MAP_SIZE * MoveCounter / MOVE_FRAME);
                ScrollY = -(MoveY * MAP_SIZE * MoveCounter / MOVE_FRAME);
            }
        }

        // �}�b�v�ƃv���C���[��`��
        GraphDraw(ScrollX, ScrollY);

        // ����ʂ̓��e��\��ʂɉf��
        ScreenFlip();
    }

    DxLib_End();               // �c�w���C�u�����g�p�̏I������

    return 0;                  // �\�t�g�̏I��
}

int LoadImages(void) { //�摜�Ǎ���
	if (LoadDivGraph("images/player/player.png", 16, 4, 4, 70, 90,CharacterImages) == 1)return -1; //���N��
	if((background1 = LoadGraph("images/background/street003_day.png")) == -1)return -1;// �w�i
	if ((blockImages = LoadGraph("images/block/0115_s1.png")) == -1)return -1; //�u���b�N
	
}

int GetArrayImages(int type, int num) { //type,�g�������摜�̗v�f�����w�肷�邱�ƂŁA�w�肵���摜���g����
	switch (type)
	{
	case CharacterImage: //���N
		if (0 <= num && num <= 16) {
			return CharacterImages[num];
		}
		else { return -1; }
		break;
	}
}


// �}�b�v�ƃv���C���[�̕`��֐�
void GraphDraw(int ScrollX, int ScrollY)
{
    int j, i;
    int MapDrawPointX, MapDrawPointY;     // �`�悷��}�b�v���W�l
    int DrawMapChipNumX, DrawMapChipNumY; // �`�悷��}�b�v�`�b�v�̐�

    // �`�悷��}�b�v�`�b�v�̐����Z�b�g
    DrawMapChipNumX = 1280 / MAP_SIZE + 2;
    DrawMapChipNumY = 720 / MAP_SIZE + 2;

    // ��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
    MapDrawPointX = character.getCharacter_X() - (DrawMapChipNumX / 2 - 1);
    MapDrawPointY = character.getCharacter_Y() - (DrawMapChipNumY / 2 - 1);

    // �}�b�v��`��
    for (i = -1; i < DrawMapChipNumY; i++)
    {
        for (j = -1; j < DrawMapChipNumX; j++)
        {
            // ��ʂ���͂ݏo���ʒu�Ȃ�`�悵�Ȃ�
            if (j + MapDrawPointX < 0 || i + MapDrawPointY < 0 ||
                j + MapDrawPointX >= MapData[MapNo].Width || i + MapDrawPointY >= MapData[MapNo].Height) continue;

            // �}�b�v�f�[�^���O��������l�p��`�悷��
            if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 0)
            {
                 DrawBox(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY,
                     j * MAP_SIZE + MAP_SIZE + ScrollX, i * MAP_SIZE + MAP_SIZE + ScrollY,
                     GetColor(255, 0, 0), TRUE);
            }
        }
    }
}