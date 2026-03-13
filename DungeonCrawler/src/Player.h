#pragma once

class Player
{
private:
    float x;
    float y;
    float speed;

public:
    Player();
    void Update(float dt);
    void Draw();
};