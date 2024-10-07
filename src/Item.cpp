//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include "../include/Item.h"
#include "../include/Room.h"

std::string Item::getName() const{
    return _name;
};

std::string Item::getDescription() const{
    return _description;
}

std::optional<std::variant<Creature*, Room*>> Item::getOwner(){
    return _owner;
}
void Item::setOwner(std::variant<Creature*, Room*> newOwner){
    _owner = newOwner;
}