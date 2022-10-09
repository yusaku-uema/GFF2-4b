#pragma once

class Character
{
private:
	float x, y; //横ｘ、縦y
	float speed; //少年の移動速度
	bool moveflg; //移動可否フラグ(壁にぶつかっていないかなど）
	bool leftflg;//左に向かっているのか判断フラグ
public:
	Character(); //コンストラクタ
	void DrawCharacter();  //描画と移動処理
	float getCharacter_X(float); //少年X座標
	float getCharacter_Y(float); //少年Y座標
	~Character(); //デストラクタ
	
};


 
