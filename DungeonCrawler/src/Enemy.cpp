#include "Enemy.h"
#include "raylib.h"
#include <cmath>

Enemy::Enemy() {
	x = 0;
	y = 0;
	speed = 100;
	alive = true;
	detectionRange = 300;
	health = 3;
}

void Enemy::Draw() {
	if (!alive) {
		return;
	}

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
	if (!alive) {
		return;
	}

	float dx = playerX - x;
	float dy = playerY - y;
	float distance = sqrt(dx * dx + dy * dy);

	if (distance < detectionRange && distance > 0.0f) {
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

void Enemy::TakeDamage(int amount) {
	if (!alive) {
		return;
	}

	health -= amount;

	if (health <= 0) {
		health = 0;
		alive = false;
	}
}

bool Enemy::IsDead() const {
	return !alive;
}