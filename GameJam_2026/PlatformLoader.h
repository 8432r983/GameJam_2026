#pragma once

#include <vector>
#include "Platform.h"

class PlatformLoader
{
	std::vector<Platform> m_platforms;

public:
	
	void clearPlatforms();
	void addPlatform(const Platform platform);
	void drawPlatforms();
	int getPlatformsCnt();
	Platform getPlatform(const int& indx);
	long long getDist(const Vector2& point, const int& indx);
};

