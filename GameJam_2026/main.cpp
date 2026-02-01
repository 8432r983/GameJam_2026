#include "raylib.h"
#include "Platform.h"
#include "Player.h"
#include "Enemy1.h"
#include "PlatformHandler.h"
#include <iostream>
#include "Projectile.h"
#include "Mask.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);
	int crFrame = 0;
	int animFrame = 0;
    int enemyFrameUpdate = 0;

	
	//PLAYER
    Player player(200, 50, screenWidth, screenHeight);
	//Enemy1 enemy1(600, 180, 0);
	Mask mask(400, 300);

    //TEXTURES
	Texture2D playerUP_texture = LoadTexture("./textures/hammer.png");
    Texture2D playerDOWN_texture = LoadTexture("./textures/legs.png");
	Texture2D playerDOWN_JUMP_texture = LoadTexture("./textures/legs_jump.png");
	Texture2D enemy1_texture = LoadTexture("./textures/enemy1.png");
	Texture2D platform_texture = LoadTexture("./textures/platform.png");

    

    Rectangle playerUP_source = { 0.0f, 0.0f, playerUP_texture.width / 2, playerUP_texture.height };
    Rectangle playerUP_dest = { 0.0f , 0.0f, player.width, player.height * 0.75};

    Rectangle playerDOWN_source = { 0.0f, 0.0f, playerDOWN_texture.width / 6, playerDOWN_texture.height };
    Rectangle playerDOWN_dest = { 0.0f , player.height * 0.75, player.width, player.height * 0.25 };

    //Rectangle enemy1_source = { 0.0f, 0.0f, enemy1_texture.width / 2, enemy1_texture.height };
    //Rectangle enemy1_dest = { 0.0f , 0.0f, enemy1.width, enemy1.height };
    //Rectangle proj_dest = { 0.0f - enemy1.width / 2 , 0.0f - enemy1.height / 2, enemy1.width, enemy1.height };

    Texture2D curTexture;

    PlatformHandler platformHandler(screenWidth, screenHeight, 563, &player, enemy1_texture);
    
    //CAMERA
    Camera2D camera = { 0 };
    camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f }; 
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.35f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
		
        //2D CAMERA

        camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f };
        BeginMode2D(camera);

        ClearBackground(GRAY);

        platformHandler.updateMap();

        player.move();
        player.onFloor = false;
		for (int i = 0; i < platformHandler.m_loader.getPlatformsCnt(); i++) {
            player.colidingCheck(platformHandler.m_loader.getPlatform(i));
        }
        player.dash();
        player.updatePosition();        

        if (IsKeyPressed(KEY_G)) {
            camera.zoom += -0.02f;
        }

		//TEXTURES DRAWING// 
        //std::cout << player.hitting << " " << CheckCollisionRecs(player.hitbox_player, mask.hitbox_mask)  << " " << enemy1.cooldown << '\n';
		//DrawRectangle( (float)player.posX, (float)player.posY, player.width, player.height, BLUE);
        //DrawRectangle((float)enemy1.posX, (float)enemy1.posY, enemy1.width, enemy1.height, GREEN);
        
        //ANIMATION FRAMES CONTROL
        if (crFrame < 60) crFrame++;
        else crFrame = 0;

        if (crFrame % 4 == 0) {
            if (animFrame < 3) animFrame++;
            else animFrame = 0;
        }

		//PLAYER TEXTURES
		//hammer animation
        if (player.hitting == true) {
            playerUP_source.x = playerUP_texture.width / 2 * 1;
        }
		else if (animFrame > 2) playerUP_source.x = playerUP_texture.width / 2 * 0; player.hitting = false;

        DrawTexturePro(playerUP_texture, playerUP_source, playerUP_dest, { -1 * (float)player.posX, -1 * (float)player.posY }, 0, WHITE);
        

		//legs animation
		//Running animation
        if (player.running == true && player.inAir == false) {
            playerDOWN_source.x = playerDOWN_texture.width / 6 * ((animFrame % 4) + 1);
            if (playerDOWN_source.width < 0) playerDOWN_source.width = -1 * playerDOWN_texture.width / 6;
            else playerDOWN_source.width = playerDOWN_texture.width / 6;
			curTexture = playerDOWN_texture;
        }
        else if (player.inJump == true && player.inAir == true) {
            playerDOWN_source.x = playerDOWN_JUMP_texture.width / 5 * 1;
            if (playerDOWN_source.width < 0) playerDOWN_source.width = -1 * playerDOWN_texture.width / 5;
            else playerDOWN_source.width = playerDOWN_texture.width / 5;
			curTexture = playerDOWN_JUMP_texture;
        }
        else if (player.inJump == false && player.inAir == true) {
            playerDOWN_source.x = playerDOWN_JUMP_texture.width / 5 * 3;
            if (playerDOWN_source.width < 0) playerDOWN_source.width = -1 * playerDOWN_texture.width / 5;
            else playerDOWN_source.width = playerDOWN_texture.width / 5;
            curTexture = playerDOWN_JUMP_texture;
        }
        else { 
            playerDOWN_source.x = playerDOWN_texture.width / 6 * 0;
			if (playerDOWN_source.width < 0) playerDOWN_source.width = -1 * playerDOWN_texture.width / 6;
            else playerDOWN_source.width = playerDOWN_texture.width / 6;
            curTexture = playerDOWN_texture;
        }

        //flip textures based on facing direction
        if (player.facing == 'R' && playerUP_source.width > 0 && playerDOWN_source.width > 0) {
            playerUP_source.width *= -1;
            playerDOWN_source.width *= -1;
        }
        else if (player.facing == 'L' && playerUP_source.width < 0 && playerDOWN_source.width < 0) {
            playerUP_source.width *= -1;
            playerDOWN_source.width *= -1;
        }

        
        DrawTexturePro(curTexture, playerDOWN_source, playerDOWN_dest, { -1 * (float)player.posX, -1 * (float)player.posY }, 0, WHITE);

		
        //DrawText(TextFormat("Frame time: %i", crFrame), 10, 30, 20, DARKGRAY);

		//ENEMY TEXTURES

        //FLIPPING
        
        //if (enemy1.posX < player.posX && enemy1_source.width > 0) {
        //    enemy1_source.width *= -1;
        //}
        //else if (enemy1.posX > player.posX && enemy1_source.width < 0) {
        //    enemy1_source.width *= -1;
        //}
        
		//textures end
        
        player.hit();

		//enemy1.update(player.width, player.height, player.posX, player.posY, player.hitbox_player, player.dmg, player.hitting, enemy1_texture, enemy1_source, enemy1_dest, proj_dest);
		//mask.update(player.hitbox_player);

        platformHandler.m_loader.drawPlatforms();

        EndDrawing();
    }
    
    UnloadTexture(playerUP_texture);
    UnloadTexture(playerDOWN_texture);
    CloseWindow();

    return 0;
}