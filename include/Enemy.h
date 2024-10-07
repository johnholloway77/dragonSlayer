//
// Created by jholloway on 10/7/24.
//

#include <vector>
#include <string>
#include "Weapon.h"
#include "Creature.h"

#ifndef DRAGONSLAYER_ENEMY_H
#define DRAGONSLAYER_ENEMY_H

class Enemy : public Creature{

public:
    Enemy(const std::string& name, int health, const std::string& desc) : Creature(name, health, desc){};

    std::string getType() const override{
        return "Enemy";
    }

    std::string attack(Creature* creature, Weapon *weapon);

    ~Enemy(){};
};

#endif //DRAGONSLAYER_ENEMY_H
