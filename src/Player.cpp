//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "../include/Item.h"
#include "../include/Player.h"



std::string Player::listInventory(){
    std::string response = getName() + " has the following items\n";
    for(const Item* item : _inventory){
        response += "- " + item->getName() + " Type: "  + item->getType() + "\n";
        response += "\t" + (item->getDescription().empty() ? "Nothing is known about this item" : item->getDescription()) +  "\n";
    }
    return response;
}

void Player::addToInventory(Item* item) {

    _inventory.push_back(item);
}
