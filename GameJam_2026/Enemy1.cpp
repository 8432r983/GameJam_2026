#include "Enemy1.h"
#include <stdlib.h>
#include <algorithm>

//(enemy1.posX + enemy1.width / 2, enemy1.posY + enemy1.height / 2, player.posX + player.width / 2, player.posY + player.height / 2);
Enemy1::Enemy1(long long id, Texture2D texture)
{
	posX = 0; //position X
	posY = 0; //position Y

	m_texture = texture;

	height = 100 * 1.8; //enemy height	
	width = 80 * 1.5; //enemy width

	cooldown = 150;
	proj = Projectile(posX, posY, posX, posY);
	proj.destroy = true;

	m_enemySource = { 0.0f, 0.0f, (float)m_texture.width / 2, (float)m_texture.height };
	m_enemyDest = { 0.0f , 0.0f, width, height };
	m_projDest = { 0.0f - width / 2 , 0.0f - height / 2, width, height };

	count = 0;

	speed = 5.5f;

	enemyID = id;

	health = 30;

	alive = true;
}


void Enemy1::drawEnemy1()
{
	DrawRectangle(posX, posY, width, height, BLANK);
}

void Enemy1::moveEnemy1()
{
	if (dir) {
		if (abs(posX - endPos.x) <= speed) posX = endPos.x;
		if (abs(posY - endPos.y) <= speed) posY = endPos.y;

		posX += speed * (endPos.x - posX > 0) - speed * (endPos.x - posX < 0);
		posY += speed * (endPos.y - posY > 0) - speed * (endPos.y - posY < 0);

		if (posX == endPos.x && posY == endPos.y) dir = !dir;
	}
	else {
		if (abs(posX - startPos.x) <= speed) posX = startPos.x;
		if (abs(posY - startPos.y) <= speed) posY = startPos.y;

		posX += speed * (startPos.x - posX > 0) - speed * (startPos.x - posX < 0);
		posY += speed * (startPos.y - posY > 0) - speed * (startPos.y - posY < 0);

		if (posX == startPos.x && posY == startPos.y) dir = !dir;
	}
}

void Enemy1::playerDetection()
{
	int x = m_player->posX;
	int y = m_player->posY;

	long int d;
	d = sqrt((x - posX) * (x - posX) + (y - posY) * (y - posY));
	if (d < 620) {
		playerInRange = true;
	}
	else {
		playerInRange = false;
	}
}

void Enemy1::attack()
{
	int pw = m_player->width;
	int ph = m_player->width;
	int ppx = m_player->posX;
	int ppy = m_player->posY;

	proj = Projectile(posX + width / 2, posY + height / 2, ppx + pw / 2, ppy + ph / 2);
	proj.destroy = false;
	cooldown = 150;
}

void Enemy1::takeDamage()
{
	int dmg = m_player->dmg;
	Rectangle player_hitbox = m_player->hitbox_player;
	bool player_hitting = m_player->hitting;

	if (CheckCollisionRecs(hitbox_enemy, player_hitbox) && player_hitting == true) {
		health -= dmg;
	}
	if (health <= 0) {
		alive = false;
	}
}

void Enemy1::update()
{
	if (alive) {
		if (count < 60) count++;
		else count = 0;
		if (count % 2 == 0) moveEnemy1();
		drawEnemy1();
		if (cooldown != 0) cooldown--;
		if (playerInRange && cooldown == 0) attack();
		playerDetection();
		proj.update();
		takeDamage();
		hitbox_enemy = { (float)posX, (float)posY, width, height };

		if (crFrame < 60) crFrame++;
		else crFrame = 0;

		if (crFrame % 15 == 0) {
			m_enemySource.x = m_texture.width / 2 * enemyFrameUpdate;
			enemyFrameUpdate++;
			if (enemyFrameUpdate > 2) enemyFrameUpdate = 0;
		}

		if (posX < m_player->posX && width > 0) {
			width *= -1;
		}
		else if (posX > m_player->posX && width < 0) {
			width *= -1;
		}

		DrawTexturePro(m_texture, m_enemySource, m_enemyDest, { -1 * (float)posX, -1 * (float)posY }, 0, CLITERAL(Color){ 255, 255, 255, 255 });
		DrawTexturePro(m_texture, m_enemySource, m_projDest, { -1 * (float)proj.curPosX, -1 * (float)proj.curPosY }, 0, CLITERAL(Color){ 144, 3, 3, 128 });
	}
}
