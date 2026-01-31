#pragma once
#include <raylib.h>
class Enemy1
{
public:
	int posX;
	int posY;

	int startX;

	float height = 100;
	float width = 80;

	int damage = 10;

	Enemy1(int x, int y);

	void drawEnemy1();
	void moveEnemy1();
	
};

