#include "Mask.h"
#include <iostream>

Mask::Mask()
{
	posX = 0;
	posY = 0;
	size = 50.0f;
	hitbox_mask = { (float)posX, (float)posY, size, size };
	isCollected = false;
}

void Mask::drawMask()
{
	DrawRectangle(posX, posY, size, size, GREEN);
}
void Mask::collected()
{
	if (CheckCollisionRecs(hitbox_mask, player->hitbox_player)) isCollected = true;
}
void Mask::update()
{
	if (!isCollected) { 
		collected();
		drawMask(); 
	}
}