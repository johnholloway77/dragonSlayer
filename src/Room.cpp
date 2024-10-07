//
// Created by jholloway on 10/6/24.
//

#include <string>
#include <vector>
#include "../include/Item.h"
#include "../include/Room.h"
#include "../include/Creature.h"

Room* Room::getNorth(){
    return _north;
}

Room* Room::getEast() {
    return _east;
}
Room* Room::getSouth() {
    return _south;
};

Room* Room::getWest(){
    return _west;
}

std::string Room::lookNorth() {
    if(_north == nullptr){
        return "There is nothing to the north";
    } else{
        return _north->getName();
    }
}

std::string Room::lookEast() {
    if(_east == nullptr){
        return "There is nothing to the east";
    } else{

        return _east->getName();
    }
}

std::string Room::lookSouth() {
    if(_south == nullptr){
        return "There is nothing to the south";
    }
    return _south->getName();
}

std::string Room::lookWest() {
    if(_west == nullptr) return "There is nothing to the west";
    return _west->getName();
}

std::string Room::getName(){
    return _name;
}
std::string Room::getDescription(){
    return _description;
};
std::string Room::listItems(){
    std::string response;
    for(const Item* item : _inventory){
        response += "- " + item->getName() + "\n";
    }
    return response;
}

void Room::addItem(Item* item) {
    if(!item->getOwner().has_value()){
        item->setOwner(this);
    }
    else{
        std::visit([item](auto&& owner){
            owner->removeItem(item);
        }, item->getOwner().value());


        item->setOwner(this);
    }

    _inventory.push_back(item);
}

void Room::removeItem(Item* item) {
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
}