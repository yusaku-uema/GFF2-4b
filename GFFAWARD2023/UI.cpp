#include"UI.h"

UI ui;

UI::UI() {
	TimeLimit = 6;
	Time = TimeLimit / 6;
	x = 0;
	Angle = 0;
	angle = 0;
	flg = TRUE;
}

int UI::ClockNeedleMove() {

	if (Timer % Time == 0 && flg == TRUE) {
		
		angle = Angle + (DX_PI / 6 * x);
		
		rotation2D(&X, &Y, 400, 100, 400, 300, angle);

		Angle += DX_PI / 360;
		if (Angle > DX_PI)/*Angle -= DX_PI*/flg=FALSE;
	}
	
	return 0;
}

int UI::UIDraw() {
	DrawRotaGraph(150, 150, 1, DX_PI / 180 * 0, img_clock, TRUE, FALSE);
	DrawRotaGraph(225, 125, 0.1, DX_PI / 180 * 0, img_sun, TRUE, FALSE);
	DrawRotaGraph(75, 125, 0.1, DX_PI / 180 * 0, img_moon, TRUE, FALSE);
	DrawRotaGraph(150, 150, 0.5, angle, img_clockneedle, TRUE, FALSE);

	return 0;
}

void UI::rotation2D(int* X, int* Y, int x, int y, int xc, int yc, double Angle) {
	*X = int((x - xc) * cos(Angle) - (y - yc) * sin(Angle) + xc);
	*Y = int((x - xc) * sin(Angle) + (y - yc) * cos(Angle) + yc);
}

int UI::GameOver() {
	if (TimeLimit == Timer) {
 		flg = FALSE;
	}
	else if (TimeLimit != Timer) {
		Timer = GetNowCount() / 1000;
	}
	return 0;
}