#pragma once
#include "Room.h"
#include <vector>

class Map {
public:
	static const int MAP_HEIGHT = 40;
	static const int MAP_WIDTH = 40;
	static const int TILE_SIZE = 16;
	void Generate();
	void Draw(int offsetX, int offsetY);
private:
	int dungeon[MAP_HEIGHT][MAP_WIDTH];
	std::vector<Room> rooms;
};

