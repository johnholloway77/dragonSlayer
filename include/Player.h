//
// Created by jholloway on 10/6/24.
//

#include <vector>
#include "Item.h"
#include "Creature.h"

#ifndef DRAGONSLAYER_PLAYER_H
#define DRAGONSLAYER_PLAYER_H

class Player : public Creature{

public:
    Player(const std::string& name, int health) : Creature(name, health){};

    std::string getType() const override{
        return "Player";
    }

    std::string listInventory();


    void addToInventory(Item* item);
    //void removeFromImventory();

    ~Player(){};
};

#endif //DRAGONSLAYER_PLAYER_H
