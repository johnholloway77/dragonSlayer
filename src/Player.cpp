//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "../include/Item.h"
#include "../include/Player.h"

std::string Player::getName() {
    return this->name;
}

std::string Player::listInventory(){
    std::string response = getName() + " has the following items\n";
    for(const Item* item : inventory){
        response += "- " + item->getName() + "\n";
    }
    return response;
}

void Player::addToInventory(Item* item) {

    inventory.push_back(item);
}