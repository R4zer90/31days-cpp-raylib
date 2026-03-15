#include "Player.h"
#include "raylib.h"

Player::Player(){
    x = 100;
    y = 100;
    speed = 200;
}

void Player::Update(float dt, const Map& map) {
    if (IsKeyDown(KEY_W)) {
        float newY = y - speed * dt;
        int row = newY / Map::TILE_SIZE;
        int col = x / Map::TILE_SIZE;

        if (!map.IsWall(row, col))
            y = newY;
    }

    if (IsKeyDown(KEY_S)) {
        float newY = y + speed * dt;
        int row = newY / Map::TILE_SIZE;
        int col = x / Map::TILE_SIZE;

        if (!map.IsWall(row, col))
            y = newY;
    }

    if (IsKeyDown(KEY_A)) {
        float newX = x - speed * dt;
        int row = y / Map::TILE_SIZE;
        int col = newX / Map::TILE_SIZE;

        if (!map.IsWall(row, col))
            x = newX;
    }

    if (IsKeyDown(KEY_D)) {
        float newX = x + speed * dt;
        int row = y / Map::TILE_SIZE;
        int col = newX / Map::TILE_SIZE;

        if (!map.IsWall(row, col))
            x = newX;
    }
}

void Player::Draw(){
    DrawCircle(x, y, 8, GREEN);
}

float Player::GetX() const {
    return x;
}

float Player::GetY() const {
    return y;
}

void Player::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}