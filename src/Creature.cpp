//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include <string>
#include <vector>
#ifdef __linux__
    #include <algorithm>
#endif

#include "../include/Creature.h"
#include "../include/Room.h"
#include "../include/Food.h"

std::string Creature::getName() {
    return _name;
}

std::string Creature::getDescription() {
    return _description;
}

void Creature::addItem(Item* item){

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

void Creature::removeItem(Item *item) {
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());
    _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item), _inventory.end());

}

Room* Creature::getCurrentRoom() {
    return _currentRoom;
}

void Creature::setCurrentRoom(Room *room) {
    if(_currentRoom){
        _currentRoom = room;
        //room->addCreature()
    }
    else{
        _currentRoom->removeCreature(this);
        _currentRoom = room;
    }

}

std::string Creature::useItem(Item* item){
    std::string response = "You can not use " + item->getName() + " that way";
    if(Food *food = dynamic_cast<Food*>(item)){
        _health += food->getHealth();

        response = _name + " ate " + food->getName() + " for " + std::to_string(food->getHealth()) + " health points";

        //remove item from owner's vector and delete
        std::visit([item](auto&& owner){
            owner->removeItem(item);
        }, item->getOwner().value());
        delete item;
        ;
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