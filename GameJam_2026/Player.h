#pragma once

#include <raylib.h>
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
	float jump;
	float dashSpeed;

	bool ground;


	Player(int x, int y);

	void leftright();
	void jumping();
	void dash();
	void move();
	void drawPlayer();
	void movement();
	

}; 

