#include "Coin.h"
#include "raylib.h"

Coin::Coin(float startX, float startY) {
	x = startX;
	y = startY;
	collected = false;
}

void Coin::Draw() {
	if (!collected) {
		DrawRing(Vector2{ x, y }, 10, 20, 0, 360, 32, GOLD);
	}
}

bool Coin::IsCollected() const {
	return collected;
}

void Coin::Collect() {
	collected = true;
}