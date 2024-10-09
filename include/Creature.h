//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_CREATURE_H
#define DRAGONSLAYER_CREATURE_H

#include "Item.h"
#include "Room.h"

class Item;

class Creature {
 protected:
  std::string _name;
  int _health;
  std::string _description;
  std::vector<Item*> _inventory;
  bool _alive;
  Room* _currentRoom = nullptr;

  void _setDescription(std::string newDesc){
    _description = newDesc;
  }

 public:
  Creature(const std::string& name, int health) : _name(name), _health(health) {
    _alive = true;
  };
  Creature(const std::string& name, int health, const std::string& desc)
      : _name(name), _health(health), _description(desc) {
    _alive = true;
  };
  virtual ~Creature(){};

  virtual std::string getType() const = 0;
  void addItem(Item* item);
  void removeItem(Item* item);

  Room* getCurrentRoom();
  void setCurrentRoom(Room* room);

  std::string getName();
  std::string getDescription();
  std::string useItem(Item* item);
  int getHealth();
  void hurt(int damage);
  bool isAlive();
  virtual std::string attack(Creature *creature, Item* item);
  virtual std::string attack(Creature *creature);

  std::vector<Item*> getInventory();
};

#endif  // DRAGONSLAYER_CREATURE_H
