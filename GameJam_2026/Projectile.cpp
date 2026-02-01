#include "Projectile.h"
#include <math.h>
#define PI 3.141592654

Projectile::Projectile(int x1, int y1, int x2, int y2)
{
	posX1 = x1; //position X start
	posY1 = y1; //position Y start

	posX2 = x2; //position X target
	posY2 = y2; //position Y target

	curPosX = posX1;
	curPosY = posY1;

	height = 100 * 1.8; //projectile height	
	width = 80 * 1.5; //projectile width

	destroy = false;

	range = 620;

	proj_speed = 0.03;

	hitbox_projectile = { (float)curPosX, (float)curPosY, width, height };

	

}

Projectile::Projectile()
{
	
}
void Projectile::move(){
	float scale;

	Vector2 direction = { (float)(posX2 - posX1), (float)(posY2 - posY1) };
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	scale = length /= range;

	Vector2 normalizedDir = { direction.x / scale, direction.y / scale };

	angle = (atan(normalizedDir.x / normalizedDir.y) * 180) / PI;

	velX = normalizedDir.x * proj_speed;
	velY = normalizedDir.y * proj_speed;

	curPosX += velX;
	curPosY += velY;

	if (curPosX == posX1 + normalizedDir.x) {
		destroy = true;
	}
	

}

void Projectile::drawProjectile()
{	
	if(!destroy) DrawRectangle(curPosX, curPosY, width, height, RED);
}

void Projectile::update() {
	move();
	//drawProjectile();
}
