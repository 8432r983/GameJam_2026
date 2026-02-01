#include "Track.h"
#include <iostream>
#include <stdlib.h>
Track::Track() {

	InitAudioDevice();
	main_theme = LoadMusicStream("tracks/fuga.mp3");
	enemy_theme = LoadMusicStream("tracks/rebirth.mp3");
	main_theme.looping = true;


	PlayMusicStream(main_theme);
	PlayMusicStream(enemy_theme);
	

}



void Track::updateMusic(bool enemyNearby) {

	
	

	if (enemyNearby) {
		/*
		if (cur == 1) {

		float volume1 = 0.0f;
		float volume2 = 1.0f;

			for (int i = 0; i < 100; i++) {
				SetMusicVolume(enemy_theme, volume1);
				SetMusicVolume(main_theme, volume2);
				UpdateMusicStream(enemy_theme);
				UpdateMusicStream(main_theme);
				volume1 += 0.01f;
				volume2 -= 0.01f;

			}
		cur = 2;
		}*/


		cur_theme = enemy_theme;
		std::cout << "Cur theme enemy" << '\n';

		PauseMusicStream(main_theme);
		ResumeMusicStream(cur_theme);
		
	}
	else {

		cur_theme = main_theme;
		std::cout << "Cur theme main" << '\n';

		StopMusicStream(enemy_theme);
		PlayMusicStream(enemy_theme);
		//PauseMusicStream(enemy_theme);
		ResumeMusicStream(cur_theme);
		
	}
	
	UpdateMusicStream(cur_theme);
}


