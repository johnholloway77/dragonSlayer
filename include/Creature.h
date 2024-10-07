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
    int _health;
    std::string _description;
    std::vector<Item*> _inventory;
    bool _alive;

public:
    Creature(const std::string& name, int health) : _name(name), _health(health) {
        _alive = true;
    };
    Creature(const std::string& name, int health, const std::string& desc) : _name(name), _health(health), _description(desc) {
        _alive = true;
    };
    virtual ~Creature(){};

    virtual std::string getType() const = 0;
    void addItem(Item* item);
    void removeItem(Item* item);

    std::string getName();
    std::string getDescription();
    std::string useItem(Item* item);
    int getHealth();
    void hurt(int damage);
    bool isAlive();

    std::vector<Item*> getInventory();
};

#endif //DRAGONSLAYER_CREATURE_H
