#include "raylib.h"

int main()
{
    float paddleP1 = 260.0f;
    float paddleAI = 260.0f;
    float paddleSpeed = 400.0f;
    float aiSpeed = 320.0f;
    const int paddleHeight = 80;
    const int paddleWidth = 20;
    const int screenWidth = 800;
    const int screenHeight = 600;
    float ballY = screenHeight / 2;
    float ballX = screenWidth / 2;
    const float deadZone = 10.0f;
    float ballVelX = 250.0f;
    float ballVelY = 180.0f;
    const float ballRadius = 10.0f;
    int scoreP1 = 0;
    int scoreAI = 0;
    int leftScoreX = screenWidth / 2 - 60;
    int rightScoreX = screenWidth / 2 + 20;
    float aiOffset = 0.0f;

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
        float targetY = ballY + aiOffset;
        if (targetY < centerAI - deadZone){
            paddleAI -= aiSpeed * dt;
        }
        else if (targetY > centerAI + deadZone) {
            paddleAI += aiSpeed * dt;
        }
        if (paddleAI < 0) {
            paddleAI = 0;
        }
        if (paddleAI > (screenHeight - paddleHeight))
            paddleAI = screenHeight - paddleHeight;
        
        //Drawing Paddle AI 
        DrawRectangle((screenWidth-paddleWidth), paddleAI, paddleWidth, paddleHeight, WHITE);

        //Move the Ball
        ballX += ballVelX * dt;
        ballY += ballVelY * dt;

        if (ballY - ballRadius <= 0) {
            ballVelY *= -1;
        }

        if (ballY + ballRadius >= screenHeight) {
            ballVelY *= -1;
        }

        //Drawing Ball
        DrawCircle(ballX, ballY, ballRadius, WHITE);

        //Drawing Points
        DrawText(TextFormat("%i", scoreP1), leftScoreX, 5, 40, WHITE);
        DrawText(TextFormat("%i", scoreAI), rightScoreX, 5, 40, WHITE);

        //Collision System
        Rectangle p1Rect{0, paddleP1, paddleWidth, paddleHeight};
        Rectangle aiRect{(screenWidth - paddleWidth), paddleAI,paddleWidth, paddleHeight };
        Vector2 ballPos{ ballX , ballY };
        
        if (CheckCollisionCircleRec(ballPos , ballRadius, p1Rect)){
            if(ballVelX < 0){
            ballVelX *= -1;
            aiOffset = GetRandomValue(-120, 120);
            }
        }
        if (CheckCollisionCircleRec(ballPos, ballRadius, aiRect)) {
            if (ballVelX > 0) {
                ballVelX *= -1;
            }
        }
        
        //Point System
        if (ballX - ballRadius < 0) {
            ballY = screenHeight / 2;
            ballX = screenWidth / 2;
            ballVelX *= -1;
            scoreAI++;
            
        }
        else if (ballX + ballRadius > screenWidth) {
            ballY = screenHeight / 2;
            ballX = screenWidth / 2;
            ballVelX *= -1;
            scoreP1++;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
