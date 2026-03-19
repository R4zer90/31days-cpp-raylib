#pragma once
#include "Map.h"

class Enemy {
private:
	float x;
	float y;
	float speed;
	bool alive;
	float detectionRange;
	int health;

public:
	Enemy();
	void Draw();
	void SetPosition(float newX, float newY);
	float GetX() const;
	float GetY() const;
	void Update(float dt, float playerX, float playerY, const Map& map);
	void TakeDamage(int amount);
	bool IsDead() const;
};