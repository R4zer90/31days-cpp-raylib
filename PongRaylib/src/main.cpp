#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Pong");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(380, 280, 40, 40, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}