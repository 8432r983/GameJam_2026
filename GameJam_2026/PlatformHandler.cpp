#include "PlatformHandler.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <memory>

unsigned int PlatformHandler::getSeedFromCoord(const Vector2& coord)
{
	return (int)(coord.x) << 16 + (int)(coord.y);
}

long long PlatformHandler::createID(int posX, int posY)
{
	long long res = (long long)((long long)posX << 32) + (long long)posY;
	return res;
}

PlatformHandler::PlatformHandler(int screenWidth, int screenHeight, int seed, Player* player, Texture2D enemyTexture)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_seed = seed;

	m_player = player;
	m_enemyTexture = enemyTexture;

	initialPlatform.width = initPlatWidth;
	initialPlatform.height = DEFAULT_HEIGHT;
	initialPlatform.pos.x = screenWidth / 2 - initPlatWidth / 2;
	initialPlatform.pos.y = screenHeight / 2;

	m_loader.addPlatform(initialPlatform);
}

Vector2 PlatformHandler::getRndPlatformRow(const int& vertLim, const int& horzLim, const Vector2 pos, const int& startwidth)
{
	int posX = pos.x + startwidth;

	int MinY = pos.y;
	int MaxY = pos.y;

	auto getRndVert = [](const int& vlim) {
		return ( rand() % (2 * vlim) ) - vlim;
	};

	auto getRndDist = []() {
		return (rand() % (MAX_PLAT_DIST - MIN_PLAT_DIST)) + MIN_PLAT_DIST;
	};

	auto getRndWidth = []() {
		return (rand() % (WIDTH_MAX - WIDTH_MIN)) + WIDTH_MIN;
	};

	int newWidth, newPosX, newPosY;

	while (posX <= pos.x + horzLim) {
		newWidth = getRndWidth();
		newPosX = posX + getRndDist();
		newPosY = pos.y + getRndVert(vertLim);
		
		m_loader.addPlatform({ newWidth, DEFAULT_HEIGHT, newPosX, newPosY });

		MinY = std::min(MinY, newPosY);
		MaxY = std::max(MaxY, newPosY);
		posX = newPosX + newWidth;
	}
	
	posX = pos.x;

	while (posX >= pos.x - horzLim) {
		newWidth = getRndWidth();
		newPosX = posX - getRndDist() - newWidth;
		newPosY = pos.y + getRndVert(vertLim);

		m_loader.addPlatform({ newWidth, DEFAULT_HEIGHT, newPosX, newPosY });

		MinY = std::min(MinY, newPosY);
		MaxY = std::max(MaxY, newPosY);
		posX = newPosX;
	}

	return { (float)MinY, (float)MaxY };
}

void PlatformHandler::getRndPlatforms(const int& heightLim, const int& widthLim, const Vector2 pos, const int& startwidth)
{
	int posY = pos.y;

	Vector2 chunkId = getScreenChunkPos(pos);
	srand(getSeedFromCoord(chunkId) + m_seed);
	
	Vector2 ylims = getRndPlatformRow(MAX_ROW_HEIGHT, widthLim, pos, startwidth);

	int MinY = ylims.x;
	int MaxY = ylims.y;

	Vector2 newPos = pos;

	posY = MaxY + MAX_ROW_HEIGHT * 4;
	while (posY <= pos.y+heightLim) {
		ylims = getRndPlatformRow(MAX_ROW_HEIGHT, widthLim, {pos.x, (float)posY}, 0);
		posY = ylims.y + MAX_ROW_HEIGHT * 4;
	}

	posY = MinY - MAX_ROW_HEIGHT * 4;
	while (posY >= pos.y - heightLim) {
		ylims = getRndPlatformRow(MAX_ROW_HEIGHT, widthLim, { pos.x, (float)posY }, 0);
		posY = ylims.x - MAX_ROW_HEIGHT * 4;
	}
}

void PlatformHandler::cleanupPlatforms(const Vector2& playerPos, const long long& limDist)
{
	std::vector<Platform> newPlatforms;
	std::unordered_map<long long, bool> mep;

	for (int i = 0; i < m_loader.getPlatformsCnt(); i++) {
		long long dist = m_loader.getDist(playerPos, i);
		int posx = m_loader.getPlatform(i).pos.x;
		int posy = m_loader.getPlatform(i).pos.y;

		if (dist <= limDist && !mep[createID(posx,posy)]) {
			newPlatforms.push_back(m_loader.getPlatform(i));
			mep[createID(posx, posy)] = true;
		}
	}
	m_loader.clearPlatforms();
	for (int i = 0; i < newPlatforms.size(); i++) {
		m_loader.addPlatform(newPlatforms[i]);
	}
}

void PlatformHandler::updateMap()
{
	float playerX = m_player->posX;
	float playerY = m_player->posY;

	Vector2 chunkp = getScreenChunkPos({ playerX, playerY });
	Vector2 pastchunkp = { -1,-1 };

	if (pastchunkp.x != chunkp.x || pastchunkp.y != chunkp.y) {

		int chpx = chunkp.x;
		int chpy = chunkp.y;

		for (int i = -RENDER_DISTANCE; i <= RENDER_DISTANCE; i++) {
			for (int j = -RENDER_DISTANCE; j <= RENDER_DISTANCE; j++) {
				int dchpx = chpx + i;
				int dchpy = chpy + j;

				Vector2 drawPos = { dchpx * m_screenWidth, dchpy * m_screenHeight };

				if (dchpx % 3 == 0 && dchpy % 3 == 0) {
					getRndPlatforms(m_screenHeight, m_screenWidth, drawPos, initialPlatform.width);
				}
			}
		}

		pastchunkp = chunkp;
		long long limDist = (long long)sqrt((m_screenWidth) * (m_screenWidth) + 
											(m_screenHeight) * (m_screenHeight)) * RENDER_DISTANCE;
		cleanupPlatforms({ playerX, playerY }, limDist);

		for (int i = 0; i < m_loader.getPlatformsCnt(); i++) {
			Platform p = m_loader.getPlatform(i);
			if (p.pos.x != initialPlatform.pos.x && p.pos.y != initialPlatform.pos.y) spawnRandomThing(p);
		}

		cleanupEnemies(limDist);
		
		std::cout << enemies.size() << " " << m_loader.getPlatformsCnt() << '\n';

		// update and draw all enemies
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].update();
			if (!enemies[i].alive) {
				clearedPlat[enemies[i].enemyID] = true;
			}
		}
	}
}

void PlatformHandler::spawnRandomEnemy(const Platform& plat)
{
	int px = m_player->posX;
	int py = m_player->posY;

	double dist = sqrt((px - plat.pos.x) * (px - plat.pos.x) + (py - plat.pos.y) * (py - plat.pos.y));
	if (dist <= 1000.f) return;
	
	long long ID = createID(plat.pos.x, plat.pos.y);
	if (platBusy[ID]) return;
	platBusy[ID] = true;

	Enemy1 newEnemy(ID, m_enemyTexture);

	newEnemy.m_player = m_player;
	
	newEnemy.health = (rand() % (MAX_ENEMY_HEALTH - MIN_ENEMY_HEALTH)) + MIN_ENEMY_HEALTH;
	
	newEnemy.startPos = { plat.pos.x + newEnemy.width / 2, plat.pos.y - newEnemy.height };
	newEnemy.endPos = { plat.pos.x + plat.width - newEnemy.width / 2, plat.pos.y - newEnemy.height };
	
	newEnemy.posX = plat.pos.x + newEnemy.width / 2;
	newEnemy.posY = plat.pos.y - newEnemy.height;
	
	newEnemy.crFrame = rand() % 10;
	
	enemies.push_back(newEnemy);
}

void PlatformHandler::cleanupEnemies(const long long& limDist)
{
	std::vector<Enemy1> newEnemies;
	std::unordered_map<long long, bool> mep;

	for (int i = 0; i < enemies.size(); i++) {
		int eX = enemies[i].posX; int pX = m_player->posX;
		int eY = enemies[i].posY; int pY = m_player->posY;
		
		long long dist = sqrt((pX - eX) * (pX - eX) + (pY - eY) * (pY - eY));

		if (dist <= limDist && !mep[createID(eX, eY)]) {
			newEnemies.push_back(enemies[i]);
			mep[createID(eX, eY)] = true;
		}
	}
	
	enemies.clear();

	for (int i = 0; i < newEnemies.size(); i++) {
		enemies.push_back(newEnemies[i]);
	}
}

void PlatformHandler::updateEnemies()
{
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].update();
	}
}

void PlatformHandler::spawnRandomThing(const Platform& plat)
{
	int rnd = rand() % 100;

	if (rnd >= 0 && rnd < MASK_SPAWN_PROB) {
		//spawnRandomMask(plat);
	}
	else if (rnd >= MASK_SPAWN_PROB && rnd < MASK_SPAWN_PROB + ENEMY_SPAWN_PROB) {
		if ((float)enemies.size() / (float)m_loader.getPlatformsCnt() <= (float)ENEMY_SPAWN_PROB / 100.0) {
			spawnRandomEnemy(plat);
		}
	}
}

Vector2 PlatformHandler::getScreenChunkPos(const Vector2& playerPos)
{
	Vector2 res;
	res.x = (int)(playerPos.x / m_screenWidth);
	res.y = (int)(playerPos.y / m_screenHeight);
	return res;  
}
