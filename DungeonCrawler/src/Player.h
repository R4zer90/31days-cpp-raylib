#pragma once
#include "Map.h"

class Player
{
private:
    float x;
    float y;
    float speed;

public:
    Player();
    void Update(float dt, const Map& map);
    void Draw();
    void SetPosition(float newX, float newY);
    float GetX() const;
    float GetY() const;
};