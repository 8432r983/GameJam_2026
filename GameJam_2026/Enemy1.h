#pragma once
#include <raylib.h>
#include "Projectile.h"

class Enemy1
{
public:
	int posX;
	int posY;

	int velX;
	int startX;

	float height;
	float width;
	Projectile proj;

	int damage = 10;

	bool playerInRange = false;

	int cooldown;

	int count;

	Rectangle hitbox_enemy;
	
	int health;

	bool alive;



	Enemy1(int x, int y);

	void drawEnemy1();
	void moveEnemy1();
	void playerDetection(int x, int y);
	void attack(float pw, float ph, float ppx, float ppy);
	void takeDamage(int dmg, Rectangle player_hitbox, bool player_hitting);
	void update(float pw, float ph, float ppx, float ppy, Rectangle hitbox_player, int dmg, bool player_hitting, Texture enemy1_texture, Rectangle enemy1_source, Rectangle enemy1_dest, Rectangle proj_dest);
	
};

