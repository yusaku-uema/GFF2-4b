#include"map.h"
#include"character.h"

Map::Map() {
	MapNo = 0;
}

// �}�b�v�ƃv���C���[�̕`��֐�
void Map::GraphDraw(int ScrollX, int ScrollY)
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
               /* DrawBox(j * MAP_SIZE + ScrollX, i * MAP_SIZE + ScrollY,
                    j * MAP_SIZE + MAP_SIZE + ScrollX, i * MAP_SIZE + MAP_SIZE + ScrollY,
                    GetColor(255, 0, 0), TRUE);*/
            }
        }
    }
}