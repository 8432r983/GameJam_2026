#pragma once

#include <raylib.h>

class Platform
{
public:
	int width;
	int height;

	Vector2 pos;

	Color color;

	Platform();
	Platform(int w, int h, int x, int y);

	bool isColliding(const int& x, const int& y);
	void changeColor(Color newColor);
	void drawPlatform();
};