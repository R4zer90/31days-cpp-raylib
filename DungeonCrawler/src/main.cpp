#include "raylib.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <cmath>

int main() {
	int screenHeight = 1080;
	int screenWidth = 1920;
	int mapWidthPixels = Map::MAP_WIDTH * Map::TILE_SIZE;
	int mapHeightPixels = Map::MAP_HEIGHT * Map::TILE_SIZE;
		
	InitWindow(screenWidth,screenHeight,"DungeonCrawler");
	ToggleFullscreen();
	SetTargetFPS(120);
	Map map;
	map.Generate();
	Player player;
	Vector2 spawnPosition = map.GetPlayerSpawnPosition();
	player.SetPosition(spawnPosition.x, spawnPosition.y);

	Camera2D camera = { 0 };
	camera.target = Vector2{ 0.0f, 0.0f };
	camera.offset = Vector2{ screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 2.0f;

	std::vector<Enemy> enemies;
	const std::vector<Room>& rooms = map.GetRooms();
	for (int i = 1; i < rooms.size(); i++) {
		Enemy enemy;

		int centerCol = rooms[i].x + rooms[i].width / 2;
		int centerRow = rooms[i].y + rooms[i].height / 2;

		float spawnX = centerCol * Map::TILE_SIZE + Map::TILE_SIZE / 2.0f;
		float spawnY = centerRow * Map::TILE_SIZE + Map::TILE_SIZE / 2.0f;

		enemy.SetPosition(spawnX, spawnY);

		enemies.push_back(enemy);
	}

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		player.Update(dt, map);
		for (Enemy& enemy : enemies) {
			enemy.Update(dt, player.GetX(), player.GetY(), map);

			if (CheckCollisionCircles(
				Vector2{ player.GetX(), player.GetY() }, 8.0f,
				Vector2{ enemy.GetX(), enemy.GetY() }, 8.0f)) {
				player.TakeDamage(1);
			}

			float dx = enemy.GetX() - player.GetX();
			float dy = enemy.GetY() - player.GetY();
			float distance = sqrt(dx * dx + dy * dy);

			if (distance < 50.0f && player.CanAttack()) {
				enemy.TakeDamage(1);
				player.ResetAttackTimer();
			}
		}

		float camX = player.GetX();
		float camY = player.GetY();

		float halfScreenWidth = screenWidth / (2.0f * camera.zoom);
		float halfScreenHeight = screenHeight / (2.0f * camera.zoom);

		if (camX < halfScreenWidth) camX = halfScreenWidth;
		if (camY < halfScreenHeight) camY = halfScreenHeight;

		if (camX > mapWidthPixels - halfScreenWidth) camX = mapWidthPixels - halfScreenWidth;
		if (camY > mapHeightPixels - halfScreenHeight) camY = mapHeightPixels - halfScreenHeight;

		camera.target = Vector2{ camX, camY };
		BeginDrawing();
		ClearBackground(BLACK);
		BeginMode2D(camera);
		map.Draw(camera, screenWidth, screenHeight);
		player.Draw();
		for (Enemy& enemy : enemies) {
			enemy.Draw();
		}
		EndMode2D();

		DrawText(TextFormat("HP: %i / %i", player.GetHealth(), player.GetMaxHealth()), 20, 20, 30, GREEN);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}