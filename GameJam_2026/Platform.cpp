#include "Platform.h"

Platform::Platform()
{
	width = 0;
	height = 0;
	pos.x = 0;
	pos.y = 0;
	color = BLACK;
}

Platform::Platform(int w, int h, int x, int y)
{
	width = w;
	height = h;
	pos.x = x;
	pos.y = y;
	color = BLACK;
}

bool Platform::isColliding(const int& x, const int& y)
{
	return x >= pos.x && x <= pos.x + width && y >= pos.y && y <= pos.y + height;
}

void Platform::changeColor(Color newColor)
{
	color = newColor;
}

void Platform::drawPlatform()
{
	DrawRectangle(pos.x, pos.y, width, height, color);
}
