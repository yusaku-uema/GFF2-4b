#pragma once
#include "AbstractScene.h"


class End :
    public AbstractScene
{
private:
    int g_end_image;
public:
    //�R���X�g���N�^
    End();
    //�f�X�g���N�^
    ~End() {}
    //�`��ȊO�̍X�V�����s
    AbstractScene* Update() override;
    //�`��Ɋւ��邱�Ƃ�����
    void Draw() const override;
};

