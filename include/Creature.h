//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_CREATURE_H
#define DRAGONSLAYER_CREATURE_H

#include "Item.h"

class Creature{
protected:
    std::string _name;
    int _health;
    std::vector<Item*> _inventory;
    bool _alive;

public:
    Creature(const std::string& name, int health) : _name(name), _health(health) {
        _alive = true;
    };
    virtual std::string getType() const = 0;

    std::string getName();
    int getHealth();
    void hurt(int damage);
    bool isAlive();
    std::vector<Item*> getInventory();
};

#endif //DRAGONSLAYER_CREATURE_H
