#pragma once
#include "AbstractScene.h"


class Title :
    public AbstractScene
{
private:
    int g_title_image;
    int g_drawingtime; //文字描画処理
public:
    //コンストラクタ
    Title();
    //デストラクタ
    ~Title() {}
    //描画以外の更新を実行
    AbstractScene* Update() override;
    //描画に関することを実装
    void Draw() const override;
};
