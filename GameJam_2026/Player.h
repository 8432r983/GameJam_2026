#pragma once

#include <raylib.h>
#include "Platform.h"

class Player
{
public:
	int posX;
	int posY;

	int m_screenWidth;
	int m_screenHeight;

	float height;
	float width;

	float velX;
	float velY;

	float speed;
	float friction;
	float jumpForce;
	
	float dashSpeed;
	float dashDiffX;
	float dashDiffY;

	int dashCnts;

	float gravity;

	int isColidingTime;
	int isDashingTime;

	bool isDashing;
	bool onFloor;

	Rectangle floorCheck;

	Player(int x, int y, int screenWidth, int screenHeight);

	void move();
	void dash();
	void updatePosition();
	void drawPlayer();
	void colidingCheck(const Platform& platform);
}; 

