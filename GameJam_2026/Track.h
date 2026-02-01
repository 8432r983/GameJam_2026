#pragma once
#include <raylib.h>
#include <string>

class Track {

public:

    Music current_music;
    Music splash_music;
    Music combat_music;
    Music chill_music;
    Music intro_music;

    bool current;

    float timePlayed;

    Track();

    void ResetMusic();
    void StartGameMusic();
    void ChangeMusic();
    void IntroMusic();
    void NormalLength();

};


