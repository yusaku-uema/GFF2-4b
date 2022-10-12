#pragma once

class Character
{
private:
	float x, y; //横ｘ、縦y
	float speed; //少年の移動速度
	bool moveflg; //移動可否フラグ(壁にぶつかっていないかなど）
	bool leftflg;//左に向かっているのか判断フラグ
	float MoveX, MoveY;// 各方向に移動する量
	int MoveCounter;// 移動し始めてから何フレーム経過したかを保持する変数
	int Move; //移動中
public:
	Character(); //コンストラクタ
	void DrawCharacter();  //描画と移動処理
	float getCharacter_X(); //少年X座標
	float getCharacter_Y(); //少年Y座標
	float getMoveX(); //移動量取得
	float getMoveY(); //移動量所得
	//~Character(); //デストラクタ
	
};


 
