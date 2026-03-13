#include "raylib.h"
#include "Map.h"
#include "Player.h"

int main() {
	int screenHeight = 600;
	int screenWidth = 800;
	int mapWidthPixels = Map::MAP_WIDTH * Map::TILE_SIZE;
	int mapHeightPixels = Map::MAP_HEIGHT * Map::TILE_SIZE;
	int offsetX = (screenWidth - mapWidthPixels) / 2;
	int	offsetY = (screenHeight - mapHeightPixels) / 2;
	
	InitWindow(screenWidth,screenHeight,"DungeonCrawler");
	SetTargetFPS(120);
	Map map;
	map.Generate();
	Player player;

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		player.Update(dt);
		BeginDrawing();
		ClearBackground(BLACK);
		map.Draw(offsetX, offsetY);
		player.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}