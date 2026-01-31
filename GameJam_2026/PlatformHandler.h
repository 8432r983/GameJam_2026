#pragma once

#include <random>
#include "PlatformLoader.h"

const int DEFAULT_HEIGHT = 35;
const int WIDTH_MIN = 160;
const int WIDTH_MAX = 280;

const int MIN_PLAT_DIST = 80;
const int MAX_PLAT_DIST = 200;

const int initPlatWidth = 200;

const int MAX_ROW_HEIGHT = 3 * DEFAULT_HEIGHT;

const int RENDER_DISTANCE = 3;

class PlatformHandler
{
public:

	int m_screenWidth;
	int m_screenHeight;
	int m_seed;

	Platform initialPlatform;

	PlatformLoader m_loader;

	unsigned int getSeedFromCoord(const Vector2& coord);

	PlatformHandler(int screenWidth, int screenHeight, int seed);
	Vector2 getRndPlatformRow(const int& vertLim, const int& horzLim, const Vector2 pos, const int& startwidth);
	void getRndPlatforms(const int& heightLim, const int& widthLim, const Vector2 pos, const int& startwidth);
	void cleanupPlatforms(const Vector2& playerPos, const long long& limDist);
	void updateMap(const Vector2& playerPos);
	Vector2 getScreenChunkPos(const Vector2& playerPos);
};

