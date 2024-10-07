//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_CREATURE_H
#define DRAGONSLAYER_CREATURE_H

#include "Item.h"

class Creature{
protected:
    std::string name;
    int health;
    std::vector<Item*> inventory;
    bool alive;

public:
    Creature(const std::string& name, int health) : name(name), health(health) {
        alive = true;
    };
    virtual std::string getType() const = 0;

    std::string getName();
    int getHealth();
    void hurt(int damage);
    bool isAlive();
};

#endif //DRAGONSLAYER_CREATURE_H
