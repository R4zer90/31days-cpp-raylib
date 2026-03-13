#include "Player.h"
#include "raylib.h"

Player::Player(){
    x = 100;
    y = 100;
    speed = 200;
}

void Player::Update(float dt){
    if (IsKeyDown(KEY_W)) y -= speed * dt;
    if (IsKeyDown(KEY_S)) y += speed * dt;
    if (IsKeyDown(KEY_A)) x -= speed * dt;
    if (IsKeyDown(KEY_D)) x += speed * dt;
}

void Player::Draw(){
    DrawCircle(x, y, 8, RED);
}