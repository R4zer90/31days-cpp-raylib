#pragma once

class Player;

class SaveSystem {
public:
    static void SaveGame(const Player& player);
    static bool LoadGame(Player& player);
};