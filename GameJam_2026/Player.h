#pragma once

#include <raylib.h>
#include "Platform.h"

class Player
{
public:
	int posX;
	int posY;

	float height;
	float width;



	float velocity_x;
	float velocity_y;
	float acceleration_x;
	float acceleration_y;

	float speed;
	float friction;
	float jumpForce;
	float dashSpeed;

	float gravity;

	int isColidingTime;


	Player(int x, int y);

	void move();
	void dash();
	void move();
	void drawPlayer();
	void movement();
	

}; 

