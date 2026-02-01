#pragma once

#include <random>
#include "PlatformLoader.h"
#include "Enemy1.h"
#include "Player.h"

#include <unordered_map>

const int DEFAULT_HEIGHT = 35;
const int WIDTH_MIN = 180;
const int WIDTH_MAX = 280;

const int MIN_PLAT_DIST = 80;
const int MAX_PLAT_DIST = 180;

const int initPlatWidth = 200;

const int MAX_ROW_HEIGHT = 3 * DEFAULT_HEIGHT;

const int RENDER_DISTANCE = 3;

const int MIN_ENEMY_HEALTH = 50;
const int MAX_ENEMY_HEALTH = 200;

const int MIN_ENEMY_DAMAGE = 10;
const int MAX_ENEMY_DAMAGE = 50;

const int MASK_SPAWN_PROB = 20; // x/100
const int ENEMY_SPAWN_PROB = 20; // x/100

const int MIN_SPAWN_DIST = 500;

class PlatformHandler
{
public:

	int m_screenWidth;
	int m_screenHeight;
	int m_seed;

	std::unordered_map<long long, bool> clearedPlat;
	std::unordered_map<long long, bool> platBusy;

	std::vector<Enemy1> enemies;

	Platform initialPlatform;

	Player* m_player;
	
	Texture2D m_enemyTexture;

	PlatformLoader m_loader;

	unsigned int getSeedFromCoord(const Vector2& coord);

	long long createID(int posX, int posY);

	PlatformHandler(int screenWidth, int screenHeight, int seed, Player* player, Texture2D enemyTexture);
	Vector2 getRndPlatformRow(const int& vertLim, const int& horzLim, const Vector2 pos, const int& startwidth);
	void getRndPlatforms(const int& heightLim, const int& widthLim, const Vector2 pos, const int& startwidth);
	void cleanupPlatforms(const Vector2& playerPos, const long long& limDist);
	void updateMap();
	Vector2 getScreenChunkPos(const Vector2& playerPos);

	void spawnRandomEnemy(const Platform& plat);
	void cleanupEnemies(const long long& limDist);
	void updateEnemies();

	void spawnRandomThing(const Platform& plat);
};

