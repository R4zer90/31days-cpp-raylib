#pragma once
#include "Map.h"
#include <map>
#include <string>

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
    std::map<std::string, int> inventory;

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
    void AddItem(const std::string& item, int amount);
    int GetItemCount(const std::string& item) const;
    void Heal(int amount);
};