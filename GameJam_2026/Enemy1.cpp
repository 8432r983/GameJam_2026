#include "Enemy1.h"
#include <stdlib.h>
#include <math.h>
//(enemy1.posX + enemy1.width / 2, enemy1.posY + enemy1.height / 2, player.posX + player.width / 2, player.posY + player.height / 2);
Enemy1::Enemy1(int x, int y)
{
	posX = x; //position X
	posY = y; //position Y

	velX = 1;
	startX = posX;

	height = 100 * 1.8; //enemy height	
	width = 80 * 1.5; //enemy width

	cooldown = 150;
	proj = Projectile(posX, posY, posX, posY);
	proj.destroy = true;

	count = 0;

	

	health = 30;

	alive = true;


	
}


void Enemy1::drawEnemy1()
{
	DrawRectangle(posX, posY, width, height, BLANK);
}

void Enemy1::moveEnemy1()
{
	if (abs(startX - posX) < 40) {
		posX += velX;
	}
	else { velX *= -1; posX += velX; }
}

void Enemy1::playerDetection(int x, int y)
{
	long int d;
	d = sqrt((x - posX) * (x - posX) + (y - posY) * (y - posY));
	if (d < 620) {
		playerInRange = true;
	}
	else {
		playerInRange = false;
	}
}

void Enemy1::attack(float pw, float ph, float ppx, float ppy)
{
	proj = Projectile(posX + width / 2, posY + height / 2, ppx + pw / 2, ppy + ph / 2);
	proj.destroy = false;
	cooldown = 150;
}

void Enemy1::takeDamage(int dmg, Rectangle player_hitbox, bool player_hitting)
{
	if (CheckCollisionRecs(hitbox_enemy, player_hitbox) && player_hitting == true) {
		health -= dmg;
	}
	if (health <= 0) {
		alive = false;
	}
}

void Enemy1::update(float pw, float ph, float ppx, float ppy, Rectangle hitbox_player, int dmg, bool player_hitting, Texture enemy1_texture, Rectangle enemy1_source, Rectangle enemy1_dest, Rectangle proj_dest)
{
	if (alive) {
		if (count < 60) count++;
		else count = 0;
		if (count % 2 == 0) moveEnemy1();
		drawEnemy1();
		if (cooldown != 0) cooldown--;
		if (playerInRange && cooldown == 0) attack(pw, ph, ppx, ppy);
		playerDetection(ppx + pw / 2, ppy + ph / 2);
		proj.update();
		takeDamage(dmg, hitbox_player, player_hitting);
		hitbox_enemy = { (float)posX, (float)posY, width, height };

		DrawTexturePro(enemy1_texture, enemy1_source, enemy1_dest, { -1 * (float)posX, -1 * (float)posY }, 0, CLITERAL(Color){ 255, 255, 255, 255 });
		DrawTexturePro(enemy1_texture, enemy1_source, proj_dest, { -1 * (float)proj.curPosX, -1 * (float)proj.curPosY }, 0, CLITERAL(Color){ 144, 3, 3, 128 });
	}
	

}
