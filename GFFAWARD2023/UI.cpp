#include"UI.h"

UI ui;

UI::UI(){
	TimeLimit = 60;
	Time = TimeLimit / 20;
	x = 0;
	Angle = 0;
}

int UI::ClockNeedleMove() {
	Timer = GetNowCount() / 1000;

	if (Timer % Time == 0) {
		//角度指定※DX_PIはDXライブラリで登録されてる定数でπ(ラジアンで180度)が定義されてます
		angle = Angle + (DX_PI / 6 * x);

		//座標を回転させる
		rotation2D(&X, &Y, 400, 100, 400, 300, angle);

		//基準座標回転角度加算※DX_TWO_PIはDXライブラリで登録されてる定数でπの二倍(ラジアンで360度)が定義されてます
		Angle += DX_TWO_PI / 720;
		if (Angle > DX_TWO_PI)Angle -= DX_TWO_PI;
	}
	return 0;
}

int UI::UIDraw() {
	DrawRotaGraph(150, 150, 0.5, angle, img_clockneedle, TRUE, FALSE);

	return 0;
}

void UI::rotation2D(int* X, int* Y, int x, int y, int xc, int yc, double Angle) {
	*X = int((x - xc) * cos(Angle) - (y - yc) * sin(Angle) + xc);
	*Y = int((x - xc) * sin(Angle) + (y - yc) * cos(Angle) + yc);
}