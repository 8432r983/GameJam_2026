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

	float velX;
	float velY;

	float speed;
	float friction;
	float jumpForce;
	float dashSpeed;

	float gravity;

	int isColidingTime;

	bool isDashing;
	bool isColiding;
	bool onFloor;

	char facing;
	bool running;
	bool hitting;
	bool inAir;
	bool inJump;

	Rectangle hitbox_player;
	int dmg;
	int health;

	Rectangle floorCollider;

	Player(int x, int y);

	void move();
	void dash();
	void updatePosition();
	void drawPlayer();
	void colidingCheck(const Platform& platform);
	void hit();
};