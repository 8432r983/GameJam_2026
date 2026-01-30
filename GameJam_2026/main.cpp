#include "raylib.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}