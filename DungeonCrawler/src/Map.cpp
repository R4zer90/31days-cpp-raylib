#include "Map.h"
#include "raylib.h"

void Map::Generate(){
	rooms.clear(); 

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
			dungeon[row][col] = 1;
		}
	}

	for (int i = 0; i < 5; i++) {
		Room room;
		room.width = GetRandomValue(6, 12);
		room.height = GetRandomValue(6, 12);
		room.x = GetRandomValue(1, MAP_WIDTH - room.width - 1);
		room.y = GetRandomValue(1, MAP_HEIGHT - room.height - 1);
		rooms.push_back(room);
	}


	for (int i = 0; i < rooms.size(); i++) {
		for (int row = rooms[i].y; row < rooms[i].y + rooms[i].height; row++) {
			for (int col = rooms[i].x; col < rooms[i].x + rooms[i].width; col++) {
				dungeon[row][col] = 0;
			}
		}
	}

	for (int i = 0; i < rooms.size() - 1; i++) {
		int x1 = rooms[i].x + rooms[i].width / 2;
		int y1 = rooms[i].y + rooms[i].height / 2;

		int x2 = rooms[i + 1].x + rooms[i + 1].width / 2;
		int y2 = rooms[i + 1].y + rooms[i + 1].height / 2;

		if (x1 < x2) {
			for (int x = x1; x <= x2; x++) {
				dungeon[y1][x] = 0;
			}
		}
		else {
			for (int x = x2; x <= x1; x++) {
				dungeon[y1][x] = 0;
			}
		}

		if (y1 < y2) {
			for (int y = y1; y <= y2; y++) {
				dungeon[y][x2] = 0;
			}
		}
		else {
			for (int y = y2; y <= y1; y++) {
				dungeon[y][x2] = 0;
			}
		}
	}
}

void Map::Draw(int offsetX, int offsetY){
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
			if (dungeon[row][col] == 1)
				DrawRectangle(offsetX + col * TILE_SIZE, offsetY + row * TILE_SIZE, TILE_SIZE, TILE_SIZE, WHITE);
		}
	}
}