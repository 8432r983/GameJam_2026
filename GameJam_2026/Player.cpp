#include "Player.h"
#include "Platform.h"
#include <algorithm>
#include <iostream>

const int JUMP_FRAMES_COOLDOWN = 10;
const float MAX_MOVE_SPEED = 10.f;
const int DASHING_COOLDOWN = 5;
const int MAX_DASHES = 2;

Player::Player(int x, int y, int screenWidth, int screenHeight)
{
	posX = x; //position X
	posY = y; //position Y

	m_screenWidth  = screenWidth; 
	m_screenHeight = screenHeight;

	height = 70; //200; //player height
	width = 45; //139.1; //player width
	
	velX = 0.f; 
	velY = 0.f;

	floorCheck.x = posX;
	floorCheck.width = width;
	floorCheck.height = width / 2;
	floorCheck.y = posY + height - floorCheck.height;

	speed = 1.2; //movement speed
	friction = 0.45; //friction coefficient
	jumpForce = 13.f; //jump strength
	dashSpeed = 55.f ; //dash speed
	
	dashCnts = MAX_DASHES;

	gravity = 2.f;

	isDashing = false;
	onFloor = false;

	isColidingTime = JUMP_FRAMES_COOLDOWN + 1;
	isDashingTime = DASHING_COOLDOWN + 1;
}

void Player::move()
{
	if (IsKeyDown(KEY_W) && onFloor) {
		isColidingTime = 0;
		velY -= jumpForce;
	}
	
	if (IsKeyDown(KEY_A)) {
		velX += -(speed * (onFloor) + 0.8f * speed * (!onFloor));
		velX = std::max(velX, -MAX_MOVE_SPEED);
	}
	if (IsKeyDown(KEY_D)) {
		velX += speed * (onFloor) + 0.8f * speed * (!onFloor);
		velX = std::min(velX, MAX_MOVE_SPEED);
	}
}
void Player::dash()
{
	if (IsKeyPressed(KEY_SPACE) && isDashingTime >= DASHING_COOLDOWN && dashCnts) {
		float mouseX = GetMousePosition().x;
		float mouseY = GetMousePosition().y;

		dashDiffX = mouseX - m_screenWidth/2;
		dashDiffY = mouseY - m_screenHeight/2;
		
		float len = sqrt(dashDiffX * dashDiffX + dashDiffY * dashDiffY);

		dashDiffX /= len;
		dashDiffY /= len;

		isDashingTime = 0;
		isDashing = true;

		dashCnts--;
	}
	
	if(isDashingTime < DASHING_COOLDOWN){
		velX = dashDiffX * dashSpeed;
		velY = dashDiffY * dashSpeed;
		isDashingTime++;
	}
	else if(isDashing) {
		isDashing = false;
		velX = 0; velY = 0;
	}
}
void Player::drawPlayer()
{
	DrawRectangle(posX, posY, width, height, RED);
}

void Player::colidingCheck(const Platform& platform)
{
	floorCheck.x = posX + width / 4;
	floorCheck.width = width / 2;
	floorCheck.height = width / 4;
	floorCheck.y = posY + height;

	bool pastFloor = onFloor;
	Rectangle rec = { platform.pos.x, platform.pos.y, (float)platform.width, (float)platform.height };
	onFloor = std::max(onFloor, CheckCollisionRecs(rec, floorCheck));

	if (pastFloor != onFloor && onFloor && isColidingTime >= JUMP_FRAMES_COOLDOWN) {
		posY = platform.pos.y - height;
	}

	if (onFloor) dashCnts = MAX_DASHES;

	floorCheck.x = posX + width / 4;
	floorCheck.width = width / 2;
	floorCheck.height = width / 4;
	floorCheck.y = posY + height;
}

void Player::updatePosition()
{
	velX += -friction*(velX > 0) + friction*(velX < 0);
	if (abs(velX) <= friction) velX = 0.f;

	if (isDashing) onFloor = false;

	if (isColidingTime < JUMP_FRAMES_COOLDOWN) {
		velY = -jumpForce;
	}
	else {
		if (!onFloor) {
			velY += gravity;
			velY = std::min(velY, 35.f);
		}
		else velY = 0;
	}
	isColidingTime++;

	posX += velX;
	posY += velY;
	
	//https://www.youtube.com/watch?v=5Ui51gD3uRE&list=PLCC34OHNcOtpOG96Uwh3VGkmpZ7qTB5dx&index=26
}