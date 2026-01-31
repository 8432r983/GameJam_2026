#pragma once

#include <raylib.h>

class AnimLoader
{
	public:
		Rectangle source;
		Rectangle dest;
		AnimLoader();

		void updateSource(float x, float y, float width, float height)
		{
			source.x = x;
			source.y = y;
			source.width = width;
			source.height = height;
		}
};

