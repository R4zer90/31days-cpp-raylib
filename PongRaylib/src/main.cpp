#include "raylib.h"

int main()
{
    float paddleP1 = 260.0f;
    float paddleAI = 260.0f;
    float paddleSpeed = 400.0f;
    const int paddleHeight = 80;
    const int paddleWidth = 20;
    const int screenWidth = 800;
    const int screenHeight = 600;
    float ballY = screenHeight / 2;
    float ballX = screenWidth / 2;
    const float deadZone = 10.0f;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(120);
   

    while (!WindowShouldClose()) {
        
        float dt = GetFrameTime();
       

        BeginDrawing();
        ClearBackground(BLACK);

        //Movement PaddleP1
        if (IsKeyDown(KEY_W)){
            paddleP1 -= paddleSpeed * dt;
        }
        if (IsKeyDown(KEY_S)){
            paddleP1 += paddleSpeed * dt;
        }
        if (paddleP1 < 0){
            paddleP1 = 0;
        }
        if (paddleP1 > (screenHeight - paddleHeight))
            paddleP1 = screenHeight - paddleHeight;

        //Drawing Paddle P1 
        DrawRectangle(0, paddleP1, paddleWidth, paddleHeight, WHITE); 

        //AI PaddleAI
        float centerAI = paddleAI + paddleHeight / 2;
        if (ballY < centerAI - deadZone){
            paddleAI -= paddleSpeed * dt;
        }
        else if (ballY > centerAI + deadZone) {
            paddleAI += paddleSpeed * dt;
        }
        if (paddleAI < 0) {
            paddleAI = 0;
        }
        if (paddleAI > (screenHeight - paddleHeight))
            paddleAI = screenHeight - paddleHeight;
        
        //Drawing Paddle AI 
        DrawRectangle((screenWidth-paddleWidth), paddleAI, paddleWidth, paddleHeight, WHITE);

        //Drawing Ball
        DrawCircle(ballX, ballY, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
