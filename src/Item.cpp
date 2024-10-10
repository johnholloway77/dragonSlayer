//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include "../include/Item.h"

#include <iostream>

#include "../include/Room.h"

std::string Item::getName() const { return _name; }

std::string Item::getDescription() const { return _description; }

std::optional<std::variant<Creature*, Room*>> Item::getOwner() {
  return _owner;
}
void Item::setOwner(std::variant<Creature*, Room*> newOwner) {
  _owner = newOwner;
}
