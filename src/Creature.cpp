//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "../include/Creature.h"
std::string Creature::getName() {
    return name;
}

int Creature::getHealth() {
    return health;
}

void Creature::hurt(int damage) {
    health = health - damage;
    if(health <= 0) alive = false;
}

bool Creature::isAlive(){
    return alive;
}