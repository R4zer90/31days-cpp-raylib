#include "raylib.h"
#include "Map.h"
#include "Player.h"

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

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		player.Update(dt, map);
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
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}