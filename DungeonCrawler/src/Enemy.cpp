#include "Enemy.h"
#include "raylib.h"
#include <cmath>

Enemy::Enemy(){
	x = 0;
	y = 0;
	speed = 100;
	alive = true;
	detectionRange = 300;
}

void Enemy::Draw() {
	DrawRectangle(x - 4, y - 4, 8, 8, RED);
}

void Enemy::SetPosition(float newX, float newY) {
	x = newX;
	y = newY;
}

float Enemy::GetX() const {
	return x;
}

float Enemy::GetY() const {
	return y;
}

void Enemy::Update(float dt, float playerX, float playerY, const Map& map) {
	float dx = playerX - x;
	float dy = playerY - y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < detectionRange) {
		float dirX = dx / distance;
		float dirY = dy / distance;

		float newX = x + dirX * speed * dt;
		int rowX = y / Map::TILE_SIZE;
		int colX = newX / Map::TILE_SIZE;

		if (!map.IsWall(rowX, colX)) {
			x = newX;
		}

		float newY = y + dirY * speed * dt;
		int rowY = newY / Map::TILE_SIZE;
		int colY = x / Map::TILE_SIZE;

		if (!map.IsWall(rowY, colY)) {
			y = newY;
		}
	}
}