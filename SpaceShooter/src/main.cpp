#include "raylib.h"
#include <vector>
#include <algorithm>

float clamp(float value, float min, float max) {
	if (value < min) 
	return min;	
	else if (value > max) 
	return max;	
	else
	return value;
}

struct Bullet {
	float x;
	float y;
};

int main() {
	const int screenWidth = 800;
	const int screenHeight = 600;
	const int shipMarginBottom = 50;
	float shipX = screenWidth / 2.0f;
	float shipY = screenHeight - shipMarginBottom;
	const int shipWidth = 30;
	const int shipHeight = 50;
	const float shipSpeed = 300;
	const float bulletSpeed = 500;
	const float bulletRadius = 5.0f;
	std::vector<Bullet> bullets;

	InitWindow(screenWidth, screenHeight,"SpaceShooter");
	SetTargetFPS(120);

	while (!WindowShouldClose()) {
		//##Update - Game Logic
		float dt = GetFrameTime();

		//Control ship
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
			shipX -= shipSpeed * dt;
		}
		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
			shipX += shipSpeed * dt;
		}
		shipX = clamp(shipX, shipWidth / 2, screenWidth - shipWidth / 2);
		if (IsKeyPressed(KEY_SPACE)) {
			Bullet bullet;
			bullet.x = shipX;
			bullet.y = shipY - shipHeight / 2;
			bullets.push_back(bullet);
		}
		
		//bullets logic
		for (auto& bullet : bullets) {
			bullet.y -= bulletSpeed * dt;
		}

		bullets.erase(
			std::remove_if(
				bullets.begin(),
				bullets.end(),
				[bulletRadius](Bullet bullet) {
					return bullet.y < -bulletRadius;
				}
			),
			bullets.end()
		);
	
		
		//##Drawing - Game Graphic ;)
		BeginDrawing();
		ClearBackground(BLACK);
		
		//Draw Ship
		Vector2 A = {shipX,	shipY - shipHeight / 2.0f};
		Vector2 B = {shipX - shipWidth / 2.0f,	shipY + shipHeight / 2.0f};
		Vector2 C = {shipX + shipWidth / 2.0f,	shipY + shipHeight / 2.0f};
		DrawTriangle(A, B, C, WHITE);

		//Draw Bullets 
		for (auto& bullet : bullets) {
			DrawCircle(bullet.x, bullet.y, bulletRadius, WHITE);
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}