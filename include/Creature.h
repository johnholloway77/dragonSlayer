//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_CREATURE_H_
#define INCLUDE_CREATURE_H_
#include <string>
#include <vector>

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

  void _setDescription(const std::string& newDesc) { _description = newDesc; }

 public:
  Creature(const std::string& name, int health) : _name(name), _health(health) {
    _alive = true;
  }
  Creature(const std::string& name, int health, const std::string& desc)
      : _name(name), _health(health), _description(desc) {
    _alive = true;
  }
  virtual ~Creature() {
    for (Item* item : _inventory) {
      delete item;
    }
  }

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
  virtual std::string attack(Creature* creature, Item* item);
  virtual std::string attack(Creature* creature);

  std::vector<Item*> getInventory();
};

#endif  // INCLUDE_CREATURE_H_
