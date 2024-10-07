//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_SWORD_H
#define DRAGONSLAYER_SWORD_H


#include "Item.h"

class Sword : public Item{

private:
    int _damage = 5; //default damage
public:

    std::string getType() const override{
        return "Weapon";
    }

    Sword(const std::string& name): Item(name) {};
    Sword(const std::string& name, const std::string& desc): Item(name, desc) {};
    Sword(const std::string& name, const std::string& desc, int damage): Item(name, desc) {
        _damage = damage;
    };


    int getDamage();
};


#endif //DRAGONSLAYER_SWORD_H
