//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_CREATURE_H
#define DRAGONSLAYER_CREATURE_H

#include "Item.h"

class Item;

class Creature{
protected:
    std::string _name;
    std::string _description;
    int _health;
    std::vector<Item*> _inventory;
    bool _alive;

public:
    Creature(const std::string& name, int health) : _name(name), _health(health) {
        _alive = true;
    };
    Creature(const std::string& name, int health, const std::string& desc) : _name(name), _health(health), _description(desc) {
        _alive = true;
    };
    virtual std::string getType() const = 0;
    virtual void addItem(Item* item) = 0;
    virtual void removeItem(Item* item) = 0;

    std::string getName();
    std::string getDescription();
    std::string useItem(Item* item);
    int getHealth();
    void hurt(int damage);
    bool isAlive();

    std::vector<Item*> getInventory();
};

#endif //DRAGONSLAYER_CREATURE_H
