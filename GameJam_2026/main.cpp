#include "raylib.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    float X = screenWidth / 2;
    float Y = screenHeight / 2;

    int rwidth = 50;
    int rheight = 50;

    float velx = 0;
    float vely = 0;

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(WHITE);

        if (IsKeyDown(KEY_RIGHT)) velx += 0.1f;
        if (IsKeyDown(KEY_LEFT))  velx -= 0.1f;
        if (IsKeyDown(KEY_UP))    vely -= 0.1f;
        if (IsKeyDown(KEY_DOWN))  vely += 0.1f;

        X += velx;
        Y += vely;

        if (X < 0) {
            X = 0; 
            velx = -velx;
        }
        if (X > screenWidth - rwidth) {
            X = screenWidth - rwidth;
            velx = -velx;
        }

        if (Y < 0) {
            Y = 0;
            vely = -vely;
        }
        if (Y > screenHeight - rheight) {
            Y = screenHeight - rheight;
            vely = -vely;
        }

        DrawRectangle((int)X, (int)Y, rwidth, rheight, RED);

        EndDrawing();

    }

    CloseWindow();

    return 0;
}