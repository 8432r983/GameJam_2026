#include "AnimLoader.h"

AnimLoader::AnimLoader()
{
	source = { 0.0f, 0.0f, 64.0f, 128.0f };
	dest = { 0.0f, 0.0f, 64.0f, 128.0f };
}

void AnimLoader::updateSource(float x, float y, float width, float height)
{
	dest.x = x;
	dest.y = y;
	dest.width = width;
	dest.height = height;
	source = { dest.x, dest.y, dest.width, dest.height };
}
