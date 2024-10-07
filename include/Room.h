//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_ROOM_H
#define DRAGONSLAYER_ROOM_H

#include <string>
#include <vector>
#include "Item.h"

class Room{

private:
    Room *_north = nullptr;
    Room *_east = nullptr;
    Room *_south = nullptr;
    Room *_west = nullptr;

    std::string _name;
    std::string _description;
    std::vector<Item*> _items;

public:

    Room(std::string name) : _name(name){};
    Room(std::string name, std::string desc) : _name(name), _description(desc){};

    std::string getName();
    std::string getDescription();
    std::string listItems();


    std::string lookNorth();
    std::string lookEast();
    std::string lookSouth();
    std::string lookWest();

    Room* getNorth();
    Room* getEast();
    Room* getSouth();
    Room* getWest();

    void addToItems(Item* item);
    Item* loseItem(std::string itemName);

    ~Room(){};
};

#endif //DRAGONSLAYER_ROOM_H
