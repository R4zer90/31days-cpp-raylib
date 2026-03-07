#pragma once
#include "GameObject.h"

class Coin : public GameObject {
private:
	bool collected;
public:
	Coin(float startX, float startY);
	void Draw();
	bool IsCollected() const;
	void Collect();
};