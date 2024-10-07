//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "../include/Creature.h"
std::string Creature::getName() {
    return _name;
}

int Creature::getHealth() {
    return _health;
}

void Creature::hurt(int damage) {
    _health = _health - damage;
    if(_health <= 0){
        _alive = false;
    }
}

bool Creature::isAlive(){
    return _alive;
}