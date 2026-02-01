#include "Track.h"
#include <string>

Track::Track() {
    splash_music = LoadMusicStream("tracks/fuga.mp3");
    current_music = splash_music;
    combat_music = LoadMusicStream("tracks/fuga.mp3");
    chill_music = LoadMusicStream("tracks/fuga.mp3");
    current = true;
    intro_music = LoadMusicStream("tracks/fuga.mp3");

    timePlayed = 0.0f;
}
void Track::ResetMusic() {
    StopMusicStream(current_music);
    PlayMusicStream(current_music);
}
void Track::IntroMusic() {
    current_music = intro_music;
    ResetMusic();
}

void Track::StartGameMusic() {
    current_music = chill_music;
    ResetMusic();
}
void Track::ChangeMusic() {
    current = !current;
    if (current) {
        current_music = chill_music;
        ResetMusic();
        SeekMusicStream(chill_music, timePlayed);
    }
    else {
        current_music = combat_music;
        ResetMusic();
    }
}
void Track::NormalLength() {
    timePlayed = GetMusicTimePlayed(chill_music);
}
