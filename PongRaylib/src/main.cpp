#include "raylib.h"

int main()
{
    float paddleY = 260.0f;
    float paddleSpeed = 400.0f;
    const int paddleHeight = 80;
    const int paddleWidth = 20;
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(120);
   

    while (!WindowShouldClose()) {
        
        float dt = GetFrameTime();
       

        BeginDrawing();
        ClearBackground(BLACK);
        if (IsKeyDown(KEY_W)){
            paddleY -= paddleSpeed * dt;
        }
        if (IsKeyDown(KEY_S)){
            paddleY += paddleSpeed * dt;
        }
        if (paddleY < 0){
            paddleY = 0;
        }
        if (paddleY > (screenHeight - paddleHeight))
            paddleY = screenHeight - paddleHeight;
        DrawRectangle(0, paddleY, paddleWidth, paddleHeight, WHITE); //Paletka

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
