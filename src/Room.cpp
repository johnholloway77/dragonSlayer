//
// Created by jholloway on 10/6/24.
//

#include <string>
#include <vector>
#include "../include/Item.h"
#include "../include/Room.h"

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
    for(const Item* item : _items){
        response += "- " + item->getName() + "\n";
    }
    return response;
}

void Room::addToItems(Item* item){
    _items.push_back(item);
}
Item* loseItem(std::string itemName);