#include "SaveSystem.h"
#include "Player.h"
#include <fstream>

void SaveSystem::SaveGame(const Player& player) {
    std::ofstream file("save.txt");

    if (!file.is_open())
        return;

    file << player.GetX() << "\n";
    file << player.GetY() << "\n";
    file << player.GetHealth() << "\n";
    file << player.GetItemCount("gold") << "\n";

    file.close();
}

bool SaveSystem::LoadGame(Player& player) {
    std::ifstream file("save.txt");

    if (!file.is_open())
        return false;

    float x;
    float y;
    int health;
    int gold;

    file >> x;
    file >> y;
    file >> health;
    file >> gold;

    file.close();

    player.SetPosition(x, y);
    player.SetHealth(health);
    player.SetItemCount("gold", gold);

    return true;
}