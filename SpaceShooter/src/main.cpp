#include "raylib.h"

float clamp(float value, float min, float max) {
	if (value < min) 
	return min;	
	else if (value > max) 
	return max;	
	else
	return value;
	}

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;
	const int shipMarginBottom = 50;
	float shipX = screenWidth / 2.0f;
	float shipY = screenHeight - shipMarginBottom;
	const int shipWidth = 30;
	const int shipHeight = 50;
	const float shipSpeed = 300;

	InitWindow(screenWidth, screenHeight,"SpaceShooter");
	SetTargetFPS(120);

	while (!WindowShouldClose()) {
		//##Update - Game Logic
		float dt = GetFrameTime();

		//Control
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			shipX -= shipSpeed * dt;
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			shipX += shipSpeed * dt;
		}
		shipX = clamp(shipX, shipWidth / 2, screenWidth - shipWidth / 2);
		
		//##Drawing - Game Graphic ;)
		BeginDrawing();
		ClearBackground(BLACK);
		
		//Ship
		Vector2 A = {shipX,	shipY - shipHeight / 2.0f};
		Vector2 B = {shipX - shipWidth / 2.0f,	shipY + shipHeight / 2.0f};
		Vector2 C = {shipX + shipWidth / 2.0f,	shipY + shipHeight / 2.0f};
		DrawTriangle(A, B, C, WHITE);
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}