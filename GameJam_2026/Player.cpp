#include "Player.h"

Player::Player(int x, int y)
{
	posX = x; //position X
	posY = y; //position Y

	height = 200; //player height
	width = 139.1; //player width
	
	
	velocity_x = 0; 
	velocity_y = 0;
	acceleration_x = 0;
	acceleration_y = 0;

	speed = 2; //movement speed
	friction = 0.15; //friction coefficient
	jump = 7; //jump strength
	dashSpeed = 0.015 ; //dash speed



	ground = false;
}
void Player::leftright()
{
	acceleration_x = 0;
	

	if (IsKeyDown(KEY_A)) acceleration_x += -1 * speed;
	if (IsKeyDown(KEY_D)) acceleration_x += speed;
}
	void Player::move(){
	
	acceleration_x -= velocity_x * friction;
	acceleration_y = 0.3; //gravity

	velocity_x += acceleration_x;
	velocity_y += acceleration_y;

	posX += velocity_x;
	posY += velocity_y;

	if (ground){
		velocity_y = 0;
	}
		
	//https://www.youtube.com/watch?v=5Ui51gD3uRE&list=PLCC34OHNcOtpOG96Uwh3VGkmpZ7qTB5dx&index=26
}
void Player::jumping()
{
	if (IsKeyDown(KEY_W) && ground) velocity_y += -1 * jump;
}
void Player::dash()
{	
	
	if (IsKeyDown(KEY_SPACE)) {
		if (GetMousePosition().y > posY) velocity_y += (GetMousePosition().y) * dashSpeed;
		else velocity_y += -1 * (GetMousePosition().y) * dashSpeed;
		
		if (GetMousePosition().x > posX) acceleration_x += (GetMousePosition().x) * dashSpeed;
		else acceleration_x += -1 * (GetMousePosition().x) * dashSpeed;
	}

}
void Player::drawPlayer()
{
	DrawRectangle(posX, posY, width, height, BLANK);
}
void Player::movement()
{
	move();
	leftright();
	dash();
	jumping();
	
}
