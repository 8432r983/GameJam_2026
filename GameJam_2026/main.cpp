#include "raylib.h"
#include <cmath>

#include "PlatformHandler.h"

#include <iostream>

const int screenWidth = 800;
const int screenHeight = 500;

float playerX = 400, playerY = 200;
float velX = 0.0, velY = 0.0;
float speed = 0.5f;
float fric = 0.05f;
int rad = 20;


int main(void)
{
    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);

    Camera2D camera = { 0 };

    camera.target = { playerX + 20.0f, playerY + 20.0f };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    PlatformHandler platHandler(screenWidth, screenHeight, 1);

    while (!WindowShouldClose())
    {
        if(IsKeyDown(KEY_W)) velY -= speed;
        if(IsKeyDown(KEY_A)) velX -= speed;
        if(IsKeyDown(KEY_S)) velY += speed;
        if(IsKeyDown(KEY_D)) velX += speed;

        platHandler.updateMap({ playerX, playerY });

        if (IsKeyPressed(KEY_G)) camera.zoom -= 0.02f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }
        
        playerX += velX;
        playerY += velY;

        velX -= fric * -1 * (velX <= 0) + fric * (velX > 0);
        velY -= fric * -1 * (velY <= 0) + fric * (velY > 0);

        camera.target = { playerX + 20, playerY + 20 };

        BeginDrawing();

        ClearBackground(WHITE);

        BeginMode2D(camera);

        DrawCircle((int)playerX, (int)playerY, rad, GREEN);
        platHandler.m_loader.drawPlatforms();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}