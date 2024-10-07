//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "../include/Creature.h"
#include "../include/Food.h"

std::string Creature::getName() {
    return _name;
}

std::string Creature::getDescription() {
    return _description;
}

std::string Creature::useItem(Item* item){
    std::string response = "You can not use " + item->getName() + " that way";
    if(Food *food = dynamic_cast<Food*>(item)){
        _health += food->getHealth();

        response = _name + " ate " + food->getName() + " for " + std::to_string(food->getHealth()) + " health points";
        delete food;
    }

    return response;
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

std::vector<Item*> Creature::getInventory(){
    return _inventory;
}