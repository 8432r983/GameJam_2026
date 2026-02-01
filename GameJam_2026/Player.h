#pragma once

#include <raylib.h>
#include "Platform.h"
#include <vector>
#include "Mask.h"

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
	float jumpForce0;
	
	float dashSpeed;
	float dashDiffX;
	float dashDiffY;

	int dashCnts;

	float gravity;

	int isColidingTime;
	int isDashingTime;

	bool isDashing;
	bool onFloor;

	char facing;
	bool running;
	bool hitting;
	bool inAir;
	bool inJump;

	Rectangle hitbox_player;
	int dmg;
	int dmg0;
	int health;

	Rectangle floorCollider;
	Rectangle floorCheck;

	std::vector<Texture2D> m_masks;

	Player(int x, int y, int screenWidth, int screenHeight, std::vector<Texture2D>& masks);

	void move();
	void dash();
	void updatePosition();
	void drawPlayer();
	void colidingCheck(const Platform& platform);
	void hit();
	void hasMask(int masktype);
};