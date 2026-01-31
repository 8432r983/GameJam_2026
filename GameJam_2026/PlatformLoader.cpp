#include "PlatformLoader.h"

void PlatformLoader::clearPlatforms()
{
	m_platforms.clear();
}

void PlatformLoader::addPlatform(const Platform platform)
{
	m_platforms.push_back(platform);
}

void PlatformLoader::drawPlatforms()
{
	for (Platform plat : m_platforms) {		
		plat.drawPlatform();
	}
}

int PlatformLoader::getPlatformsCnt()
{
	return (int)m_platforms.size();
}

Platform PlatformLoader::getPlatform(const int& indx)
{
	return m_platforms[indx];
}

long long PlatformLoader::getDist(const Vector2& point, const int& indx)
{
	return (long long)sqrt((point.x-m_platforms[indx].pos.x) * (point.x-m_platforms[indx].pos.x) 
						 + (point.y-m_platforms[indx].pos.y) * (point.y-m_platforms[indx].pos.y));
}
