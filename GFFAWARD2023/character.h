#pragma once

class Character
{
private:
	float x, y; //横ｘ、縦y
	float speed; //少年の移動速度
	bool moveflg; //移動可否フラグ(壁にぶつかっていないかなど）
	bool leftflg;//左に向かっているのか判断フラグ
	int Move;    // 移動しているかどうかのフラグ( 0:停止中  1:移動中 )
	int MoveX, MoveY;// 各方向に移動する量
	int MoveCounter;// 移動し始めてから何フレーム経過したかを保持する変数
public:
	Character(); //コンストラクタ
	void DrawCharacter();  //描画と移動処理
	float getCharacter_X(float); //少年X座標
	float getCharacter_Y(float); //少年Y座標
	int getMove(); //移動フラグ取得
	int getMoveX(); //移動量取得
	int getMoveY(); //移動量所得
	~Character(); //デストラクタ
	
};


 
