#pragma once
#include <raylib.h>

class Mask
{
public:
	char type;
	int Debuff;
	int Buff;
	float wh;

	void drawMask(int x, int y);

	Mask(float x);

};

