#pragma once
#include <raylib.h>
#include "Player.h"

class Mask
{
public:
	int type;
	float size;

	int posX;
	int posY;

	long long maskID;

	Player* player;

	bool isCollected;

	Rectangle hitbox_mask;

	void drawMask();
	void collected();
	void update();

	Mask();

};

