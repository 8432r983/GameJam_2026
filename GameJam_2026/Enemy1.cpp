#include "Enemy1.h"

Enemy1::Enemy1(int x, int y)
{
	posX = x; //position X
	posY = y; //position Y

	height = 100; //enemy height	
	width = 80; //enemy width
	
}


void Enemy1::drawEnemy1()
{
	DrawRectangle(posX, posY, width, height, BLANK);
}

void Enemy1::moveEnemy1()
{
	//jessir jorking it rn
}

