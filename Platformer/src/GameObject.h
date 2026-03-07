#pragma once

class GameObject {
protected:
	float x;
	float y;
public:
	float GetX() const { return x; }
	float GetY() const { return y; }
};