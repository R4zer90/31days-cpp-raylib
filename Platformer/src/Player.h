#pragma once
#include "GameObject.h"

class Player : public GameObject {
private:
	float speed;
	float velocityY;
	float gravity;
	bool onGround;
public:
	Player();
	void Update(float dt);
	void Draw();
	void SetOnGround(bool value);
	void Land(float groundY);
};