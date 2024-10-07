//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "../include/Item.h"
#include "../include/Player.h"
#include "../include/Sword.h"



std::string Player::listInventory(){
    std::string response = getName() + " has the following items\n";
    for(const Item* item : _inventory){
        response += "- " + item->getName() + " Type: "  + item->getType() + "\n";
        response += "\t" + (item->getDescription().empty() ? "Nothing is known about this item" : item->getDescription()) +  "\n";
    }
    return response;
}

void Player::addItem(Item* item){
    _inventory.push_back(item);
}

void Player::removeItem(Item *item) {
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
}


std::string Player::attack() {
    return "You attack at nothing and look like a fool!";
}

std::string Player::attack(Creature* creature){
    std::string response;
    int damage;
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(1, 10);
    damage = distribution(randomDevice);
    creature->hurt(damage);

    response += creature->getName() + " was attacked with bare hands for " + std::to_string(damage) + " points of damage";

    return response;
}

std::string Player::attack(Creature* creature, Item* item){
    std::string response;
    int damage = 0;

    if(Sword* s = dynamic_cast<Sword*>(item)){

        std::random_device randomDevice;
        std::mt19937 gen(randomDevice());
        std::uniform_int_distribution<> distribution(1, 10);
        damage = distribution(randomDevice) * s->getDamage();
        creature->hurt(damage);
        response += creature->getName() + " was attacked with " + item->getName() + " for " + std::to_string(damage) + " points of damage";

    } else{
        response += item->getName() + " is not a weapon\n";
        response += creature->getName() + " was attacked with " + item->getName() + " for " + std::to_string(damage) + " points of damage";
    }

    return response;
}