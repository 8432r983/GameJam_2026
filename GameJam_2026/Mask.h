#pragma once
#include <raylib.h>

class Mask
{
public:
	char type;
	int Debuff;
	int Buff;
	float size;

	int posX;
	int posY;

	bool isCollected;

	Rectangle hitbox_mask;

	void drawMask(int x, int y);
	void collected(Rectangle hitbox_player);
	void update(Rectangle hitbox_player);

	Mask(int x, int y);

};

