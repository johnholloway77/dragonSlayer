//
// Created by jholloway on 10/6/24.
//

#include <vector>
#include "include/item.h"

#ifndef DRAGONSLAYER_PLAYER_H
#define DRAGONSLAYER_PLAYER_H

class Player{

private:
    std::string name;
    char health = 100;
    std::vector<Item> inventory;

public:
    Player(const std::string name) : name(name){};

    std::string listInventory();

    ~Player(){};
};

#endif //DRAGONSLAYER_PLAYER_H
