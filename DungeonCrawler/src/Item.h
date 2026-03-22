#pragma once
#include <string>

class Item {
private:
    float x;
    float y;
    std::string name;
    int amount;
    bool collected;

public:
    Item(float startX, float startY, const std::string& itemName, int itemAmount);
    void Draw() const;
    float GetX() const;
    float GetY() const;
    std::string GetName() const;
    int GetAmount() const;
    bool IsCollected() const;
    void Collect();
};