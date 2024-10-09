//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_ROOM_H
#define DRAGONSLAYER_ROOM_H

#include <string>
#include <vector>

#include "Item.h"

class Item;

class Room {
 private:
  Room *_north = nullptr;
  Room *_east = nullptr;
  Room *_south = nullptr;
  Room *_west = nullptr;

  bool _accessable = true;

  std::string _name;
  std::string _description;
  std::vector<Item *> _inventory;
  std::vector<Creature *> _creatures;

 public:
  void setNorth(Room *north);

  void setEast(Room *east);

  void setSouth(Room *south);

  void setWest(Room *west);

  void setAll(Room *north, Room *east, Room *south, Room *west);

  Room(std::string name) : _name(name){};
  Room(std::string name, bool accessable, std::string desc)
      : _name(name), _accessable(accessable), _description(desc){};
  Room(std::string name, std::string desc) : _name(name), _description(desc){};

  std::string getName();
  std::string getDescription();
  std::string listItems();
  std::string listCreatures();
  bool getAccessable();

  Room *getNorth();
  Room *getEast();
  Room *getSouth();
  Room *getWest();

  void addItem(Item *item);
  void removeItem(Item *item);
  std::vector<Item *> getInventory();

  void addCreature(Creature *creature);
  void removeCreature(Creature *creature);
  std::vector<Creature *> getCreatures();


  ~Room();
};

#endif  // DRAGONSLAYER_ROOM_H
