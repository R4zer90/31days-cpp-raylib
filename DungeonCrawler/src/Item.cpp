#include "Item.h"
#include "raylib.h"

Item::Item(float startX, float startY, const std::string& itemName, int itemAmount) {
    x = startX;
    y = startY;
    name = itemName;
    amount = itemAmount;
    collected = false;
}

void Item::Draw() const {
    if (collected) {
        return;
    }

    if (name == "gold") {
        DrawCircle(x, y, 5, YELLOW);
    }
    else if (name == "potion") {
        DrawCircle(x, y, 5, BLUE);
    }
}

float Item::GetX() const {
    return x;
}

float Item::GetY() const {
    return y;
}

std::string Item::GetName() const {
    return name;
}

int Item::GetAmount() const {
    return amount;
}

bool Item::IsCollected() const {
    return collected;
}

void Item::Collect() {
    collected = true;
}