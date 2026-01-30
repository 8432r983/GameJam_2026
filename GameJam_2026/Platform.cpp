#include "Platform.h"

Platform::Platform(int w, int h, int x, int y)
{
	width = w;
	height = h;
	posX = x;
	posY = y;
	color = BLACK;
}

bool Platform::isColliding(const int& x, const int& y)
{
	return x >= posX && x <= posX + width && y >= posY && y <= posY + height;
}

void Platform::changeColor(Color newColor)
{
	color = newColor;
}

void Platform::drawPlatform()
{
	DrawRectangle(posX, posY, width, height, color);
}
