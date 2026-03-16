#pragma once
#include "Room.h"
#include <vector>
#include "raylib.h"

class Map {
public:
	static const int MAP_HEIGHT = 80;
	static const int MAP_WIDTH = 80;
	static const int TILE_SIZE = 32;
	void Generate();
	void Draw(const Camera2D& camera, int screenWidth, int screenHeight);
	bool IsWall(int row, int col) const;
	Vector2 GetPlayerSpawnPosition() const;
	const std::vector<Room>& GetRooms() const;
private:
	int dungeon[MAP_HEIGHT][MAP_WIDTH];
	std::vector<Room> rooms;
};

