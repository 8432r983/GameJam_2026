#include "Player.h"
#include <algorithm>
#include <iostream>

const int JUMP_FRAMES_COOLDOWN = 20;

Player::Player(int x, int y)
{
	posX = x; //position X
	posY = y; //position Y

	height = 100 *1.33; //200; //player height
	width = 80 *1.33; //139.1; //player width
	
	velX = 0.f; 
	velY = 0.f;

	floorCollider.x = posX;
	floorCollider.width = width;
	floorCollider.height = width / 4;
	floorCollider.y = posY + height - floorCollider.height;

	speed = 1.2; //movement speed
	friction = 0.45; //friction coefficient
	jumpForce = 9.f; //jump strength
	dashSpeed = 0.015 ; //dash speed
	
	gravity = 1.5f;

	isDashing = false;
	isColiding = false;
	onFloor = false;

	
	dmg = 10;
	health = 100;

	isColidingTime = JUMP_FRAMES_COOLDOWN + 1;
}

void Player::move()
{
	
	if (IsKeyPressed(KEY_W) && isColiding) {
		velY -= jumpForce; // jumping
		isColidingTime = 0;
	}

	if (IsKeyDown(KEY_A)) { velX -= speed; facing = 'L'; }
	if (IsKeyDown(KEY_D)) { velX += speed; facing = 'R'; }

	//check if running
	if (velX < -1 || velX > 1) {
		running = true;
	}
	else {
		running = false;
	}

	//check if in air
	if (velY < -1 || velY > 1) {
		inAir = true;
	}
	else {
		inAir = false;
	}

	//check if in jump
	if (velY < -1) {
		inJump = true;
	}
	else {
		inJump = false;
	}
	if (inAir) velY += 0.3;

}
void Player::dash()
{
	//if (IsKeyDown(KEY_SPACE)) {
	//	if (GetMousePosition().y > posY) velocity_y += (GetMousePosition().y) * dashSpeed;
	//	else velocity_y += -1 * (GetMousePosition().y) * dashSpeed;
	//
	//	if (GetMousePosition().x > posX) acceleration_x += (GetMousePosition().x) * dashSpeed;
	//	else acceleration_x += -1 * (GetMousePosition().x) * dashSpeed;
	//}
}
void Player::drawPlayer()
{
	//DrawRectangle(posX, posY, width, height, BLANK);
	DrawRectangle(posX, posY, width, height, RED);
	//DrawRectangle(floorCollider.x, floorCollider.y, floorCollider.width, floorCollider.height, YELLOW);
}

void Player::colidingCheck(const Platform& platform)
{
	isColiding = std::max(isColiding, CheckCollisionRecs(floorCollider, {platform.pos.x,platform.pos.y,(float)platform.width,(float)platform.height})
							&& !isDashing);

	floorCollider.x = posX;
	floorCollider.width = width;
	floorCollider.height = width / 4;
	floorCollider.y = posY + height - floorCollider.height;
}

void Player::updatePosition()
{
	//std::cout << isColiding << " " << posX << " " << posY << '\n';

	velX += -friction*(velX > 0) + friction*(velX < 0);
	if (abs(velX) <= friction) velX = 0.f;

	if (isColidingTime < JUMP_FRAMES_COOLDOWN) {
		velY = -jumpForce;
		isColiding = false;
	}
	else {
		if (!isColiding) {
			velY += gravity;
			velY = std::min(velY, 30.f);
		}
		else velY = 0;
	}
	isColidingTime++;

	posX += velX;
	posY += velY;
	
	hitbox_player = { (float)posX, (float)posY, width, height };
	
}

void Player::hit()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		hitting = true;
	}/*
	else {
		hitting = false;
	}*/
}