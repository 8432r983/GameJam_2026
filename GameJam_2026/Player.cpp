#include "Player.h"
#include "Platform.h"
#include <algorithm>
#include <iostream>

const int JUMP_FRAMES_COOLDOWN = 10;
const float MAX_MOVE_SPEED = 10.f;
const int DASHING_COOLDOWN = 5;
const int MAX_DASHES = 2;

const int MAX_VELOCITY_HORIZONTAL = 20.f;

Player::Player(int x, int y, int screenWidth, int screenHeight, std::vector<Texture2D>& masks)
{
	posX = x; //position X
	posY = y; //position Y

	m_screenWidth  = screenWidth; 
	m_screenHeight = screenHeight;
	
	m_masks = {};
	m_masks = { masks[0], masks[1] };

	height = 110; //200; //player height
	width = 80; //139.1; //player width
	
	velX = 0.f; 
	velY = 0.f;

	floorCheck.x = posX;
	floorCheck.width = width;
	floorCheck.height = width / 2;
	floorCheck.y = posY + height - floorCheck.height;

	speed = 1.2; //movement speed
	friction = 0.45; //friction coefficient
	jumpForce = 13.f; //jump strength
	jumpForce0 = jumpForce;
	dashSpeed = 55.f ; //dash speed
	
	dashCnts = MAX_DASHES;

	gravity = 2.f;

	isDashing = false;
	onFloor = false;

	
	dmg = 10;
	dmg0 = dmg;
	health = 100;

	isColidingTime = JUMP_FRAMES_COOLDOWN + 1;
	isDashingTime = DASHING_COOLDOWN + 1;
}

void Player::move()
{
	if (IsKeyDown(KEY_W) && onFloor) {
		isColidingTime = 0;
		velY -= jumpForce;
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

	if (velX > MAX_VELOCITY_HORIZONTAL) velX = MAX_VELOCITY_HORIZONTAL;
	if (velX < -MAX_VELOCITY_HORIZONTAL) velX = -MAX_VELOCITY_HORIZONTAL;

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

void Player::hasMask(int masktype)
{	
	Rectangle mask_source = { 0.0f, 0.0f, m_masks[0].width, m_masks[0].height};
	Rectangle mask_dest = { 0.0f , 0.0f, width, height * 0.75 };

	if (facing == 'R' && mask_source.width > 0 && mask_source.width > 0) {
		mask_source.width *= -1;
	}
	else if (facing == 'L' && mask_source.width < 0 && mask_source.width < 0) {
		mask_source.width *= -1;    
	}

	if (masktype == 0) {
		dmg = dmg0;
		jumpForce = jumpForce0;
	}
	else if (masktype == 1) {
		
		//DrawRectangle((float)posX,(float)posY, m_masks[masktype - 1].width, m_masks[masktype - 1].height, YELLOW);
		DrawTexturePro(m_masks[masktype - 1], mask_source, mask_dest, { -1 * (float)posX, -1 * (float)posY }, 0 ,WHITE);
		dmg *= 1.5;
		jumpForce = jumpForce0;

	}
	else if (masktype == 2) {

		DrawTexturePro(m_masks[masktype - 1], mask_source, mask_dest, { -1 * (float)posX, -1 * (float)posY }, 0, WHITE);
		jumpForce *= 1.5;
		dmg = dmg0;

	}
}