#pragma once
#include <raylib.h>

class Projectile
{
	public:
	int posX1; //position X start
	int posY1; //position Y start

	int posX2; //position X target
	int posY2; //position Y target

	int curPosX;
	int curPosY;

	float velX;
	float velY;

	float height;
	float width;

	bool destroy;

	float range;

	float proj_speed;
	float angle;

	Rectangle hitbox_projectile;

	void move();
	void drawProjectile();
	void update();

	Projectile(int x1, int y1, int x2, int y2);
	Projectile();
	
};

