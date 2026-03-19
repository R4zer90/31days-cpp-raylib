#pragma once
#include "Map.h"

class Player{
private:
    float x;
    float y;
    float speed;
    int health;
    int maxHealth;
    float damageTimer;
    float damageCooldown;
    float attackTimer;
    float attackCooldown;
    float attackEffectTimer;

public:
    Player();
    void Update(float dt, const Map& map);
    void Draw();
    void SetPosition(float newX, float newY);
    float GetX() const;
    float GetY() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    void TakeDamage(int amount);
    bool CanAttack() const;
    void ResetAttackTimer();
};