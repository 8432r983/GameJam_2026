#pragma once
#include <raylib.h>
#include "Projectile.h"
#include "Player.h"
#include <unordered_map>
#include <memory>

class Enemy1
{
public:
	int posX;
	int posY;

	float height;
	float width;
	Projectile proj;

	int damage = 10;

	long long enemyID;
	bool playerInRange = false;

	int cooldown;
	int count;

	Rectangle hitbox_enemy;

	Player* m_player;
	
	Texture2D m_texture;

	Rectangle m_enemySource;
	Rectangle m_enemyDest;
	Rectangle m_projDest;
	
	Vector2 startPos;
	Vector2 endPos;
	float speed;
	bool dir; // back, fourth

	int health;

	int crFrame;
	int enemyFrameUpdate;

	bool alive;

	Enemy1(long long id, Texture2D texture);

	void drawEnemy1();
	void moveEnemy1();
	void playerDetection();
	void attack();
	void takeDamage();
	void update();
};

