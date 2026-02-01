#include "Mask.h"

Mask::Mask(int x, int y)
{
	posX = x;
	posY = y;
	size = 50.0f;
	hitbox_mask = { (float)posX, (float)posY, size, size };
	isCollected = false;
}

void Mask::drawMask(int x, int y)
{
	DrawRectangle(x, y, size, size, GREEN);
}
void Mask::collected(Rectangle hitbox_player)
{
	if (CheckCollisionRecs(hitbox_mask, hitbox_player)) isCollected = true;
}
void Mask::update(Rectangle hitbox_player)
{
	if (!isCollected) { 
		collected(hitbox_player);
		drawMask(posX, posY); 
	}
}