#pragma once
#include"DxLib.h"
#include"math.h"
#include"stdlib.h"
#define _USE_MATH_DEFINES
#define PI 3.1415926535897932384626433832795f

class UI {
public:
	int Timer;
	float TimeLimit;
	int Time;
	float x;
	int X, Y;
	double Angle, angle;

	int img_clockneedle;
	int img_clock;
	int img_sun;
	int img_moon;

	UI();
	int ClockNeedleMove();
	int UIDraw();
	void rotation2D(int* X, int* Y, int x, int y, int xc, int yc, double Angle);
};

extern UI ui;