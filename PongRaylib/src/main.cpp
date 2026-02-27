#include "raylib.h"

enum class GameState
{
    MENU,
    PLAYING,
    GAMEOVER
};

// centered text on x axis
static void DrawTextCenteredX(const char* text, int y, int fontSize, Color color, int screenWidth)
{
    int textWidth = MeasureText(text, fontSize);
    int x = (screenWidth - textWidth) / 2;
    DrawText(text, x, y, fontSize, color);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    const int paddleWidth = 20;
    const int paddleHeight = 80;

    const float paddleSpeed = 400.0f;
    const float aiSpeed = 320.0f;

    const float ballRadius = 10.0f;
    const float deadZone = 10.0f;

    const int winScore = 5;

    float paddleP1 = 260.0f;
    float paddleAI = 260.0f;

    float ballX = screenWidth / 2.0f;
    float ballY = screenHeight / 2.0f;

    float ballVelX = 250.0f;
    float ballVelY = 180.0f;

    int scoreP1 = 0;
    int scoreAI = 0;

    int leftScoreX = screenWidth / 2 - 60;
    int rightScoreX = screenWidth / 2 + 20;

    float aiOffset = 0.0f;  // random offset so AI isn't perfect

    GameState currentState = GameState::MENU;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // --- menu ---
        if (currentState == GameState::MENU)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                currentState = GameState::PLAYING;
            }
        }
        else if (currentState == GameState::GAMEOVER)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                scoreP1 = 0;
                scoreAI = 0;

                ballX = screenWidth / 2.0f;
                ballY = screenHeight / 2.0f;
                ballVelX = 250.0f;
                ballVelY = 180.0f;

                paddleP1 = 260.0f;
                paddleAI = 260.0f;
                aiOffset = 0.0f;

                currentState = GameState::MENU;
            }
        }

        if (currentState == GameState::PLAYING)
        {
            if (IsKeyDown(KEY_W))
                paddleP1 -= paddleSpeed * dt;
            if (IsKeyDown(KEY_S))
                paddleP1 += paddleSpeed * dt;

            if (paddleP1 < 0)
                paddleP1 = 0;
            if (paddleP1 > (screenHeight - paddleHeight))
                paddleP1 = (float)(screenHeight - paddleHeight);

            // AI follows ball with dead zone
            float centerAI = paddleAI + paddleHeight / 2.0f;
            float targetY = ballY + aiOffset;
            if (targetY < centerAI - deadZone)
                paddleAI -= aiSpeed * dt;
            else if (targetY > centerAI + deadZone)
                paddleAI += aiSpeed * dt;

            if (paddleAI < 0)
                paddleAI = 0;
            if (paddleAI > (screenHeight - paddleHeight))
                paddleAI = (float)(screenHeight - paddleHeight);

            ballX += ballVelX * dt;
            ballY += ballVelY * dt;

            if (ballY - ballRadius <= 0)
                ballVelY *= -1;
            if (ballY + ballRadius >= screenHeight)
                ballVelY *= -1;

            // collision - check direction so ball doesn't stick to paddle
            Rectangle p1Rect{ 0, paddleP1, (float)paddleWidth, (float)paddleHeight };
            Rectangle aiRect{ (float)(screenWidth - paddleWidth), paddleAI, (float)paddleWidth, (float)paddleHeight };
            Vector2 ballPos{ ballX, ballY };

            if (CheckCollisionCircleRec(ballPos, ballRadius, p1Rect))
            {
                if (ballVelX < 0)
                {
                    ballVelX *= -1;
                    aiOffset = (float)GetRandomValue(-120, 120);
                }
            }

            if (CheckCollisionCircleRec(ballPos, ballRadius, aiRect))
            {
                if (ballVelX > 0)
                    ballVelX *= -1;
            }

            if (ballX - ballRadius < 0)
            {
                scoreAI++;
                ballX = screenWidth / 2.0f;
                ballY = screenHeight / 2.0f;
                ballVelX *= -1;
            }
            else if (ballX + ballRadius > screenWidth)
            {
                scoreP1++;
                ballX = screenWidth / 2.0f;
                ballY = screenHeight / 2.0f;
                ballVelX *= -1;
            }

            if (scoreP1 >= winScore || scoreAI >= winScore)
            {
                currentState = GameState::GAMEOVER;
            }
        }

        // --- draw ---
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(0, (int)paddleP1, paddleWidth, paddleHeight, WHITE);
        DrawRectangle(screenWidth - paddleWidth, (int)paddleAI, paddleWidth, paddleHeight, WHITE);

        if (currentState == GameState::PLAYING || currentState == GameState::GAMEOVER)
        {
            DrawCircle((int)ballX, (int)ballY, ballRadius, WHITE);
            DrawText(TextFormat("%i", scoreP1), leftScoreX, 5, 40, WHITE);
            DrawText(TextFormat("%i", scoreAI), rightScoreX, 5, 40, WHITE);
        }

        if (currentState == GameState::MENU)
        {
            DrawTextCenteredX("Press ENTER to Start", screenHeight / 2, 40, WHITE, screenWidth);
        }

        if (currentState == GameState::GAMEOVER)
        {
            DrawTextCenteredX("GAME OVER", screenHeight / 2 - 60, 50, WHITE, screenWidth);

            const char* winnerText = (scoreP1 >= winScore) ? "PLAYER WINS!" : "AI WINS!";
            DrawTextCenteredX(winnerText, screenHeight / 2, 40, WHITE, screenWidth);

            DrawTextCenteredX("Press ENTER to Restart", screenHeight / 2 + 60, 30, WHITE, screenWidth);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
