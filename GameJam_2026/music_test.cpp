#include <raylib.h>
#include "Track.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int maint(void)
{
    
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - music stream");

    Track track;

    InitAudioDevice();              // Initialize audio device
    track.current_music = LoadMusicStream("/home/nspincic/Documents/gamejam/berry-groovy-bass-trap-476603.mp3");



    PlayMusicStream(track.current_music);

    // float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
    bool pause = false;             // Music playing paused

    float pan = 0.0f;               // Default audio pan center [-1.0f..1.0f]
    SetMusicPan(track.current_music, pan);

    float volume = 0.8f;            // Default audio volume [0.0f..1.0f]
    SetMusicVolume(track.current_music, volume);

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(track.current_music);   // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (IsKeyPressed(KEY_SPACE))
        {
            track.ResetMusic();
        }
        if (IsKeyPressed(KEY_N)) {
            track.ChangeMusic();
        }
        // Pause/Resume music playing
        if (IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) PauseMusicStream(track.current_music);
            else ResumeMusicStream(track.current_music);
        }

        // Set audio pan
        if (IsKeyDown(KEY_LEFT))
        {
            pan -= 0.05f;
            if (pan < -1.0f) pan = -1.0f;
            SetMusicPan(track.current_music, pan);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            pan += 0.05f;
            if (pan > 1.0f) pan = 1.0f;
            SetMusicPan(track.current_music, pan);
        }

        // Set audio volume
        if (IsKeyDown(KEY_DOWN))
        {
            volume -= 0.05f;
            if (volume < 0.0f) volume = 0.0f;
            SetMusicVolume(track.current_music, volume);
        }
        else if (IsKeyDown(KEY_UP))
        {
            volume += 0.05f;
            if (volume > 1.0f) volume = 1.0f;
            SetMusicVolume(track.current_music, volume);
        }
        track.NormalLength();

        // Get normalized time played for current music stream


        if (track.timePlayed > 1.0f) track.timePlayed = 1.0f;   // Make sure time played is no longer than music
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, LIGHTGRAY);

        DrawText("LEFT-RIGHT for PAN CONTROL", 320, 74, 10, DARKBLUE);
        DrawRectangle(300, 100, 200, 12, LIGHTGRAY);
        DrawRectangleLines(300, 100, 200, 12, GRAY);
        DrawRectangle((int)(300 + (pan + 1.0f) / 2.0f * 200 - 5), 92, 10, 28, DARKGRAY);

        DrawRectangle(200, 200, 400, 12, LIGHTGRAY);
        //DrawRectangle(200, 200, (int)(timePlayed*400.0f), 12, MAROON);
        DrawRectangleLines(200, 200, 400, 12, GRAY);

        DrawText("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, LIGHTGRAY);
        DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, LIGHTGRAY);

        DrawText("UP-DOWN for VOLUME CONTROL", 320, 334, 10, DARKGREEN);
        DrawRectangle(300, 360, 200, 12, LIGHTGRAY);
        DrawRectangleLines(300, 360, 200, 12, GRAY);
        DrawRectangle((int)(300 + volume * 200 - 5), 352, 10, 28, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(track.current_music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
