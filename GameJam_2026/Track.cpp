#include "Track.h"
#include <iostream>
#include <stdlib.h>
Track::Track() {

	InitAudioDevice();
	main_theme = LoadMusicStream("tracks/fuga.mp3");
	enemy_theme = LoadMusicStream("tracks/rebirth.mp3");
	start_theme = LoadMusicStream("tracks/spawn_bass.mp3");
	main_theme.looping = true;


	PlayMusicStream(main_theme);
	PlayMusicStream(enemy_theme);
	PlayMusicStream(start_theme);

	

}



void Track::updateMusic(bool enemyNearby, bool instart) {

	enemyNearby = false;
	

	if (enemyNearby) {
	
		cur_theme = enemy_theme;
		//std::cout << "Cur theme enemy" << '\n';

		PauseMusicStream(main_theme);
		ResumeMusicStream(cur_theme);
		StopMusicStream(start_theme);
		
	}
	else if (instart) {
		cur_theme = start_theme;
	}
	else {

		cur_theme = main_theme;
		//std::cout << "Cur theme main" << '\n';

		StopMusicStream(enemy_theme);
		PlayMusicStream(enemy_theme);

		StopMusicStream(start_theme);

		//PauseMusicStream(enemy_theme);
		ResumeMusicStream(cur_theme);
		
	}
	
	UpdateMusicStream(cur_theme);
}


