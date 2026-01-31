#include "PlatformHandler.h"
#include <cmath>
#include <algorithm>

unsigned int PlatformHandler::getSeedFromCoord(const Vector2& coord)
{
	return (int)(coord.x) << 16 + (int)(coord.y);
}

PlatformHandler::PlatformHandler(int screenWidth, int screenHeight, int seed)
{
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_seed = seed;

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
		
		m_loader.addPlatform(Platform(newWidth, DEFAULT_HEIGHT, newPosX, newPosY));
		
		MinY = std::min(MinY, newPosY);
		MaxY = std::max(MaxY, newPosY);
		posX = newPosX + newWidth;
	}
	
	posX = pos.x;

	while (posX >= pos.x - horzLim) {
		newWidth = getRndWidth();
		newPosX = posX - getRndDist() - newWidth;
		newPosY = pos.y + getRndVert(vertLim);

		m_loader.addPlatform(Platform(newWidth, DEFAULT_HEIGHT, newPosX, newPosY));

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
	for (int i = 0; i < m_loader.getPlatformsCnt(); i++) {
		long long dist = m_loader.getDist(playerPos, i);
		if (dist <= limDist) {
			newPlatforms.push_back(m_loader.getPlatform(i));
		}
	}
	m_loader.clearPlatforms();
	for (int i = 0; i < newPlatforms.size(); i++) {
		m_loader.addPlatform(newPlatforms[i]);
	}
}

void PlatformHandler::updateMap(const Vector2& playerPos)
{
	float playerX = playerPos.x;
	float playerY = playerPos.y;

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
	}
}

Vector2 PlatformHandler::getScreenChunkPos(const Vector2& playerPos)
{
	Vector2 res;
	res.x = (int)(playerPos.x / m_screenWidth);
	res.y = (int)(playerPos.y / m_screenHeight);
	return res;  
}
