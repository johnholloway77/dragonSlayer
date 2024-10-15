//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_ROOM_H_
#define INCLUDE_ROOM_H_

#include <string>
#include <vector>

#include "Item.h"

class Item;

class Room {
 protected:
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

  explicit Room(std::string &name) : _name(name) {}
  Room(const std::string &name, bool accessable, const std::string &desc)
      : _name(name), _accessable(accessable), _description(desc) {}
  Room(const std::string &name, const std::string &desc)
      : _name(name), _description(desc) {}

  const std::string &getName();
  const std::string &getDescription();
  std::string listItems();
  std::string listCreatures();

  Room *getNorth();
  Room *getEast();
  Room *getSouth();
  Room *getWest();

  void addItem(Item *item);
  void removeItem(Item *item);
  const std::vector<Item *> &getInventory();

  void addCreature(Creature *creature);
  void removeCreature(Creature *creature);
  const std::vector<Creature *> &getCreatures();
  virtual bool isAccessable();

  ~Room();
};

#endif  // INCLUDE_ROOM_H_
