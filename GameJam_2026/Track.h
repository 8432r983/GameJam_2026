#pragma once
#include <raylib.h>
#include <string>
#include "Enemy1.h"
class Track {

public:

    Music main_theme;
    Music enemy_theme;
	Music cur_theme;
	Enemy1* enemyPtr;

	int cur = 1;


    Track();
	void updateMusic(bool enemyNearby);
	

};


