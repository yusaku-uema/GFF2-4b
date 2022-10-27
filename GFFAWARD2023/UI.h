#pragma once
#include"DxLib.h"
#include"math.h"
#define PI 3.1415926535897932384626433832795f

class UI {
public:
	int Timer;
	float TimeLimit;
	int Time;
	int img_clockneedle;
	float x;
	int X, Y;
	double Angle, angle;

	UI();
	int ClockNeedleMove();
	int UIDraw();
	void rotation2D(int* X, int* Y, int x, int y, int xc, int yc, double Angle);
};

extern UI ui;