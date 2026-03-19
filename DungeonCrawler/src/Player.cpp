#include "Player.h"
#include "raylib.h"

Player::Player(){
    x = 100;
    y = 100;
    speed = 200;
    health = 100;
    maxHealth = 100;
    damageTimer = 0.0f;
    damageCooldown = 1.0f;
    attackTimer = 0.0f;
    attackCooldown = 0.5f;
    attackEffectTimer = 0.0f;
}

void Player::Update(float dt, const Map& map) {
    damageTimer += dt;
    attackTimer += dt;
    attackEffectTimer -= dt;

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
    if (attackEffectTimer > 0.0f) {
        DrawCircleLines(x, y, 50, PURPLE);
    }
}

float Player::GetX() const {
    return x;
}

float Player::GetY() const {
    return y;
}

int Player::GetHealth() const {
    return health;
}

int Player::GetMaxHealth() const {
    return maxHealth;
}

void Player::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Player::TakeDamage(int amount) {
    if (damageTimer >= damageCooldown) {
        health -= amount;

        if (health < 0) {
            health = 0;
        }

        damageTimer = 0.0f;
    }
}

bool Player::CanAttack() const {
    return attackTimer >= attackCooldown;
}

void Player::ResetAttackTimer() {
    attackTimer = 0.0f;
    attackEffectTimer = 0.2f;
}