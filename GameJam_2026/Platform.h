#pragma once

#include <raylib.h>

class Platform
{
	int width;
	int height;

	int posX;
	int posY;

	Color color;

	Platform(int w, int h, int x, int y);

public:
	bool isColliding(const int& x, const int& y);
	void changeColor(Color newColor);
};

