#include "raylib.h"
//#include "game.cpp"

int start(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Yirniy");

    SetTargetFPS(60);        

	Texture2D startscreen_texture = LoadTexture("textures/startscreen.png");
    Texture2D startbutton_texture = LoadTexture("textures/startbutton.png");

	Rectangle startscreen_source = { 0.0f, 0.0f, (float)startscreen_texture.width, (float)startscreen_texture.height };
	Rectangle startscreen_dest = { 0.0f , 0.0f, (float)screenWidth, (float)screenHeight };

	Rectangle startbutton_source = { 0.0f, 0.0f, (float)startbutton_texture.width, (float)startbutton_texture.height };
	Rectangle startbutton_dest = { (float)(screenWidth / 2 - 350) , (float)(screenHeight / 2), 200.0f, 80.0f };

	Rectangle mouseRec = { 0.0f, 0.0f, 1.0f, 1.0f };
   
    while (!WindowShouldClose())    
    {
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexturePro(startscreen_texture, startscreen_source, startscreen_dest, { 0 , 0 } ,0 ,  WHITE);

        if (CheckCollisionRecs(mouseRec, startbutton_dest)) {
            DrawTexturePro(startbutton_texture, startbutton_source, startbutton_dest, { 0 , 0 }, 0, CLITERAL(Color){ 255, 255, 255, 200 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                break;
			}
        }
        else {
            DrawTexturePro(startbutton_texture, startbutton_source, startbutton_dest, { 0 , 0 }, 0, CLITERAL(Color){ 255, 255, 255, 255 });
        }
		
        

		mouseRec.x = (float)GetMouseX();
		mouseRec.y = (float)GetMouseY();

		



        EndDrawing();
        
    }

   
    CloseWindow();        
    

    return 0;
}