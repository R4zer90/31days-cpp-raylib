#pragma once
#include "Map.h"

class Player;
class Enemy {
private:
	float x;
	float y;
	float speed;
	bool alive;
	float detectionRange;
	int health;
	bool lootDropped;

public:
	Enemy();
	void Draw();
	void SetPosition(float newX, float newY);
	float GetX() const;
	float GetY() const;
	void Update(float dt, float playerX, float playerY, const Map& map);
	void TakeDamage(int amount);
	bool IsDead() const;
	bool HasDroppedLoot() const;
	void DropLoot(Player& player);
};