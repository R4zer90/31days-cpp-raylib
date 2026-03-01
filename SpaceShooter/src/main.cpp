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
	int score = 0;
	bool gameOver = false;


	float startX = 10;
	float startY = 10;
	int spacing = 80;
	int count = 8;
	int rows = 3;
	int columns = 8;
	int rowSpacing = 50;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			Enemy e;
			e.x = startX + c * spacing + (r % 2 == 1 ? spacing / 2 : 0);
			e.y = startY + r * rowSpacing;
			e.alive = true;
			enemies.push_back(e);
		}
	}

	InitWindow(screenWidth, screenHeight, "SpaceShooter");
	SetTargetFPS(120);

	while (!WindowShouldClose()) {
		//##Update - Game Logic
		float dt = GetFrameTime();

		//game over logic
		if (gameOver) {
			if (IsKeyPressed(KEY_ENTER)) {
				gameOver = false;
				score = 0;
				enemyDirectionX = 1;

				shipX = screenWidth / 2.0f;
				shipY = screenHeight - shipMarginBottom;

				bullets.clear();
				enemies.clear();

				//another wave (restart)
				for (int r = 0; r < rows; r++) {
					for (int c = 0; c < columns; c++) {
						Enemy e;
						e.x = startX + c * spacing + (r % 2 == 1 ? spacing / 2 : 0);
						e.y = startY + r * rowSpacing;
						e.alive = true;
						enemies.push_back(e);
					}
				}
			}
		}
		else {
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
						score++;
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

			//ship rect (for game over collision)
			float shipLeft = shipX - shipWidth / 2.0f;
			float shipRight = shipX + shipWidth / 2.0f;
			float shipTop = shipY - shipHeight / 2.0f;
			float shipBottom = shipY + shipHeight / 2.0f;

			for (auto& e : enemies) {
				if (e.alive) {
					e.x += enemySpeed * enemyDirectionX * dt;

					//enemy -> ship collision (game over)
					float enemyLeft = e.x;
					float enemyRight = e.x + enemySize;
					float enemyTop = e.y;
					float enemyBottom = e.y + enemySize;

					bool overlapX = (enemyRight >= shipLeft) && (enemyLeft <= shipRight);
					bool overlapY = (enemyBottom >= shipTop) && (enemyTop <= shipBottom);

					if (overlapX && overlapY) {
						gameOver = true;
						break;
					}
				}

				if (e.alive && (e.x <= 0 || e.x >= screenWidth - enemySize)) {
					shouldChangeDirection = true;
				}
			}

			if (!gameOver && shouldChangeDirection == true) {
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

			//another wave
			if (!gameOver && enemies.empty()) {
				for (int r = 0; r < rows; r++) {
					for (int c = 0; c < columns; c++) {
						Enemy e;
						e.x = startX + c * spacing + (r % 2 == 1 ? spacing / 2 : 0);
						e.y = startY + r * rowSpacing;
						e.alive = true;
						enemies.push_back(e);
					}
				}
			}
		}

		//##Drawing - Game Graphic ;)
		BeginDrawing();
		ClearBackground(BLACK);

		//Draw Ship
		Vector2 A = { shipX,	shipY - shipHeight / 2.0f };
		Vector2 B = { shipX - shipWidth / 2.0f,	shipY + shipHeight / 2.0f };
		Vector2 C = { shipX + shipWidth / 2.0f,	shipY + shipHeight / 2.0f };
		DrawTriangle(A, B, C, WHITE);

		//Draw Bullets 
		for (auto& bullet : bullets) {
			DrawCircle(bullet.x, bullet.y, bulletRadius, WHITE);
		}

		//Draw Enemies
		for (auto& e : enemies) {
			DrawRectangle(e.x, e.y, enemySize, enemySize, WHITE);
		}

		//Draw Score
		DrawText(TextFormat("Score: %i", score), 5, screenHeight - 40, 20, WHITE);

		//game over screen
		if (gameOver) {
			DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 40, 40, WHITE);
			DrawText("Press ENTER to restart", screenWidth / 2 - MeasureText("Press ENTER to restart", 20) / 2, screenHeight / 2 + 10, 20, WHITE);
		}

		EndDrawing();
	}
	CloseWindow();
	return 0;
}