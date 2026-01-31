#include "raylib.h"
#include "Platform.h"
#include "Player.h"

int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "GameJam 2026");

    SetTargetFPS(60);

    Player player(200, 100);
    //TEXTURE
	Texture2D playerUP_texture = LoadTexture("hammer.png");
    Texture2D playerDOWN_texture = LoadTexture("legs.png");

    GetWorkingDirectory();

    Camera2D camera = { 0 };
    camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f }; 
    camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose())
    {
            
        camera.target = Vector2{ player.posX + 20.0f, player.posY + 20.0f };

        BeginDrawing();

        BeginMode2D(camera);

        ClearBackground(WHITE);
	
		Platform platform1(400, 40, 100, 300);
		platform1.drawPlatform();

		player.ground = platform1.isColliding(player.posX + player.width, player.posY + player.height);
   
		player.movement();
        player.drawPlayer();

		DrawTextureEx(playerUP_texture, Vector2{(float) player.posX, (float) player.posY}, 0, 0.2f, WHITE);
        
        

        EndDrawing();
    }
       
    UnloadTexture(playerUP_texture);
    UnloadTexture(playerDOWN_texture);
    CloseWindow();

    return 0;
}