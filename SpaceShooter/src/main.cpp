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
	bool alive;
};

struct Enemy {
	float x;
	float y;
	bool alive;
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
	std::vector<Enemy> enemies;
	const float enemySpeed = 100.0f;
	int enemyDirectionX = 1;
	const int enemySize = 20;
	const int enemyDrop = 10;
	

	float startX = 10;
	float startY = 10;
	int spacing = 100;
	int count = 8;

	for (int i = 0; i < count; i++) {
		Enemy e;
		e.x = startX + i * spacing;
		e.y = startY;
		e.alive = true;
		enemies.push_back(e);
	}

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
			bullet.alive = true;
			bullets.push_back(bullet);
		}
		
		//bullets logic
		for (auto& bullet : bullets) {
			bullet.y -= bulletSpeed * dt;
			for (auto& e : enemies) {
				if (!e.alive) continue;

				float enemyLeft = e.x;
				float enemyRight = e.x + enemySize;
				float enemyTop = e.y;
				float enemyBottom = e.y + enemySize;

				// bullet rect (x,y as center)
				float bulletLeft = bullet.x - bulletRadius;
				float bulletRight = bullet.x + bulletRadius;
				float bulletTop = bullet.y - bulletRadius;
				float bulletBottom = bullet.y + bulletRadius;

				bool overlapX = (bulletRight >= enemyLeft) && (bulletLeft <= enemyRight);
				bool overlapY = (bulletBottom >= enemyTop) && (bulletTop <= enemyBottom);

				if (overlapX && overlapY) {
					e.alive = false;
					bullet.alive = false;
					break;
				}
			}

		}

		bullets.erase(
			std::remove_if(
				bullets.begin(),
				bullets.end(),
				[bulletRadius](const Bullet& bullet) {
					return bullet.y < -bulletRadius || !bullet.alive;
				}
			),
			bullets.end()
		);

		
	
		//enemy logic
		bool shouldChangeDirection = false;
		for (auto& e : enemies) {
			if (e.alive) {
				e.x += enemySpeed * enemyDirectionX * dt;
			}
			if (e.alive && (e.x <= 0 || e.x >= screenWidth - enemySize)) {
				shouldChangeDirection = true;
			}
		}
		if (shouldChangeDirection == true) {
			enemyDirectionX *= -1;
			for (auto& e : enemies) {
				if (e.alive) {
					e.y += enemyDrop;
					
				}
			}
		}
		
		enemies.erase(
			std::remove_if(
				enemies.begin(),
				enemies.end(),
				[](const Enemy& e) { return !e.alive; }
			),
			enemies.end()
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

		//Draw Enemies
		for (auto& e : enemies) {
			DrawRectangle(e.x, e.y, enemySize, enemySize, WHITE);
		}

		EndDrawing();
	}
	CloseWindow();
	return 0;
}