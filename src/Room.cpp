//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <string>
#include <vector>

#ifdef __linux__
#include <algorithm>
#endif

#include "../include/Creature.h"
#include "../include/Item.h"

Room::~Room() {
  for (Item* item : _inventory) {
    delete item;
  }
  for (Creature* creature : _creatures) {
    delete creature;
  }
}

Room* Room::getNorth() { return _north; }

Room* Room::getEast() { return _east; }
Room* Room::getSouth() { return _south; }

Room* Room::getWest() { return _west; }

std::string Room::getName() { return _name; }
std::string Room::getDescription() { return _description; }

std::string Room::listItems() {
  std::string response;

  std::for_each(_inventory.begin(), _inventory.end(),
                [&response](const Item* item) {
                  response += "- " + item->getName() + "\n";
                });

  return response;
}

std::string Room::listCreatures() {
  std::string response;
  if (!_creatures.empty()) {
    std::for_each(_creatures.begin(), _creatures.end(),
                  [&response](Creature* creature) {
                    response += "- " + creature->getName() + "\n";
                  });
  } else {
    response = "Nothing stands here";
  }

  return response;
}

void Room::addItem(Item* item) {
  if (!item) {
    return;  // return if null item
  }

  if (!item->getOwner().has_value()) {
    item->setOwner(this);
  } else {
    try {
      std::visit([item](auto&& owner) { owner->removeItem(item); },
                 item->getOwner().value());

      item->setOwner(this);
    } catch (const std::bad_variant_access& ex) {
      return;
    }
  }

  _inventory.push_back(item);
}

void Room::removeItem(Item* item) {
  _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item),
                   _inventory.end());
}

void Room::addCreature(Creature* creature) {
  creature->setCurrentRoom(this);
  _creatures.push_back(creature);
}

void Room::removeCreature(Creature* creature) {
  if (creature->getCurrentRoom() == nullptr) {
    return;
  }
  _creatures.erase(std::remove(_creatures.begin(), _creatures.end(), creature),
                   _creatures.end());
}

void Room::setNorth(Room* north) {
  _north = north;

  if (!north->getSouth()) {
    north->setSouth(this);
  }
}

void Room::setEast(Room* east) {
  _east = east;
  if (!east->getWest()) {
    east->setWest(this);
  }
}

void Room::setSouth(Room* south) {
  _south = south;
  if (!south->getNorth()) {
    south->setNorth(this);
  }
}

void Room::setWest(Room* west) {
  _west = west;
  if (!west->getEast()) {
    west->setEast(this);
  }
}

std::vector<Item*> Room::getInventory() { return _inventory; }

std::vector<Creature*> Room::getCreatures() { return _creatures; }
bool Room::isAccessable() { return _accessable; }
