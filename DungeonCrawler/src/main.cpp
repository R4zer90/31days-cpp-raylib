#include "raylib.h"

const int MAP_HEIGHT = 40;
const int MAP_WIDTH = 40;
int dungeon[MAP_HEIGHT][MAP_WIDTH];
const int TILE_SIZE = 16;

int main() {
	int screenHeight = 600;
	int screenWidth = 800;
	int mapWidthPixels = MAP_WIDTH * TILE_SIZE;
	int mapHeightPixels = MAP_HEIGHT * TILE_SIZE;
	int offsetX = (screenWidth - mapWidthPixels) / 2;
	int	offsetY = (screenHeight - mapHeightPixels) / 2;
	
	InitWindow(screenWidth,screenHeight,"DungeonCrawler");
	SetTargetFPS(120);

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
			dungeon[row][col] = 1;
		}
	}

	int roomWidth = GetRandomValue(6, 12);
	int roomHeight = GetRandomValue(6, 12);
	int roomX = GetRandomValue(1, MAP_WIDTH - roomWidth -1);
	int roomY = GetRandomValue(1, MAP_HEIGHT - roomHeight -1);


	for (int row = roomY; row < roomY + roomHeight; row++) {
		for (int col = roomX; col < roomX + roomWidth; col++) {
			dungeon[row][col] = 0;
		}
	}

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		//Rysowanie Œcian
		for (int row = 0; row < MAP_HEIGHT; row++) {
			for (int col = 0; col < MAP_WIDTH; col++) {
				if (dungeon[row][col] == 1)
				DrawRectangle(offsetX + col * TILE_SIZE, offsetY + row * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
			}
		}

		
		EndDrawing();
	}

	CloseWindow();
	return 0;
}