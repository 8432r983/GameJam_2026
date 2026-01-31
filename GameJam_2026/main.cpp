#include "raylib.h"
#include "Platform.h"
#include "Player.h"
#include "Enemy1.h"

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);
	int crFrame = 0;
	int animFrame = 0;
	int enemyFrame = 0;

	//PLAYER
    Player player(200, 50);
	Enemy1 enemy1(600, 300);

    //TEXTURES
	Texture2D playerUP_texture = LoadTexture("hammer.png");
    Texture2D playerDOWN_texture = LoadTexture("legs.png");
	Texture2D playerDOWN_JUMP_texture = LoadTexture("legs_jump.png");
	Texture2D enemy1_texture = LoadTexture("enemy1.png");

    Rectangle playerUP_source = { 0.0f, 0.0f, playerUP_texture.width / 2, playerUP_texture.height };
    Rectangle playerUP_dest = { 0.0f , 0.0f, player.width, player.height * 0.75};

    Rectangle playerDOWN_source = { 0.0f, 0.0f, playerDOWN_texture.width / 6, playerDOWN_texture.height };
    Rectangle playerDOWN_dest = { 0.0f , player.height * 0.75, player.width, player.height * 0.25 };

    

    Texture2D curTexture;

    
    //CAMERA
    Camera2D camera = { 0 };
    camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f }; 
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
		
        //2D CAMERA

        camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f };
        BeginMode2D(camera);

        ClearBackground(WHITE);

	    

		//LOGIC//

        //Platform placeholder
        Platform platform1(400, 40, 100, 300);
        platform1.drawPlatform();
        
		//Player Logic
		player.ground = platform1.isColliding(player.posX + player.width, player.posY + player.height);
		player.update();
        player.drawPlayer();

		//Enemy Logic
		enemy1.drawEnemy1();

        

        //logic end
		
        

		//TEXTURES DRAWING// 

        //ANIMATION FRAMES CONTROL
        if (crFrame < 60) crFrame++;
        else crFrame = 0;

        if (crFrame % 4 == 0) {
            if (animFrame < 3) animFrame++;
            else animFrame = 0;
        }

        if (crFrame % 30 == 0) {
            if (enemyFrame < 1) enemyFrame++;
            else enemyFrame = 0;
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
        Rectangle enemy1_source = { 0.0f, 0.0f, enemy1_texture.width / 2, enemy1_texture.height };
        Rectangle enemy1_dest = { 0.0f , 0.0f, enemy1.width, enemy1.height };

        enemy1_source.x = enemy1_texture.width / 2 * (enemyFrame % 2);
        DrawTexturePro(enemy1_texture, enemy1_source, enemy1_dest, { -1 * (float)enemy1.posX, -1 * (float)enemy1.posY }, 0, WHITE);
        
		//textures end
        
        

        EndDrawing();
    }
       
    UnloadTexture(playerUP_texture);
    UnloadTexture(playerDOWN_texture);
    CloseWindow();

    return 0;
}