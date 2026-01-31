#include "raylib.h"
#include <cmath>

#include "PlatformHandler.h"
#include "Player.h"

#include <iostream>

const int screenWidth = 800;
const int screenHeight = 500;

float playerX = 400, playerY = 200;
float velX = 0.0, velY = 0.0;
float speed = 0.5f;
float fric = 0.05f;
int rad = 20;

float smoothSpeed = 4.5f;

float delayedPlayerX = 0.0f;
float delayedPlayerY = 0.0f;

int main(void)
{
    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);

    Camera2D camera = { 0 };

    camera.target = { playerX + 20.0f, playerY + 20.0f };
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.85f;

    PlatformHandler platHandler(screenWidth, screenHeight, 13);

    Player mainPlayer(400,170);

    while (!WindowShouldClose())
    {
        //if(IsKeyDown(KEY_W)) velY -= speed;
        //if(IsKeyDown(KEY_A)) velX -= speed;
        //if(IsKeyDown(KEY_S)) velY += speed;
        //if(IsKeyDown(KEY_D)) velX += speed;
        
        //std::cout << platHandler.m_loader.getPlatformsCnt() << '\n';

        mainPlayer.move();
        mainPlayer.dash();
        for (int i = 0; i < platHandler.m_loader.getPlatformsCnt(); i++) {
            mainPlayer.colidingCheck(platHandler.m_loader.getPlatform(i));
        }
        mainPlayer.updatePosition();

        playerX = mainPlayer.posX;
        playerY = mainPlayer.posY;

        platHandler.updateMap({ playerX, playerY });

        if (IsKeyPressed(KEY_G)) camera.zoom -= 0.02f;

        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }
        
        smoothSpeed = std::max((abs(velX)*abs(velY)), 4.5f);

        //playerX += velX;
        //playerY += velY;
        //
        //velX -= fric * -1 * (velX <= 0) + fric * (velX > 0);
        //velY -= fric * -1 * (velY <= 0) + fric * (velY > 0);

        camera.target = { delayedPlayerX + 20.0f, delayedPlayerY + 20.0f };

        if (delayedPlayerX != playerX) {
            if (abs(delayedPlayerX - playerX) <= smoothSpeed) { delayedPlayerX = playerX; smoothSpeed = 4.5f; }
            else delayedPlayerX += -smoothSpeed * (playerX - delayedPlayerX <= 0) + smoothSpeed * (playerX - delayedPlayerX > 0);
        }

        if (delayedPlayerY != playerY) {
            if (abs(delayedPlayerY - playerY) <= smoothSpeed) { delayedPlayerY = playerY; smoothSpeed = 4.5f; }
            else delayedPlayerY += -smoothSpeed * (playerY - delayedPlayerY <= 0) + smoothSpeed * (playerY - delayedPlayerY > 0);
        }

        BeginDrawing();

        BeginMode2D(camera);

        ClearBackground(WHITE);

        BeginMode2D(camera);

        //DrawCircle((int)playerX, (int)playerY, rad, GREEN);
        mainPlayer.drawPlayer();
        platHandler.m_loader.drawPlatforms();

        EndMode2D();

        EndDrawing();
    }
       
    //UnloadTexture(playerUP_texture);
    //UnloadTexture(playerDOWN_texture);
    CloseWindow();

    return 0;
}