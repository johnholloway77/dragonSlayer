
//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <iostream>
#include <random>
#include <string>
#include <vector>
#ifdef __linux__
#include <algorithm>
#endif

#include "../include/Creature.h"
#include "../include/Food.h"
#include "../include/Item.h"
#include "../include/Weapon.h"

std::string Creature::getName() { return _name; }

std::string Creature::getDescription() { return _description; }

void Creature::addItem(Item* item) {
  if (!item->getOwner().has_value()) {
    item->setOwner(this);
  } else {
    std::visit([item](auto&& owner) { owner->removeItem(item); },
               item->getOwner().value());

    item->setOwner(this);
  }

  _inventory.push_back(item);
}

void Creature::removeItem(Item* item) {
  _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item),
                   _inventory.end());
  _inventory.erase(std::remove(_inventory.begin(), _inventory.end(), item),
                   _inventory.end());
}

Room* Creature::getCurrentRoom() { return _currentRoom; }

void Creature::setCurrentRoom(Room* room) {
  if (_currentRoom) {
    _currentRoom->removeCreature(this);
  }
  _currentRoom = room;

  if (_currentRoom) {
    _currentRoom = room;
  }
}

std::string Creature::useItem(Item* item) {
  std::string response = "You can not use " + item->getName() + " that way";

  if (Food* food = dynamic_cast<Food*>(item)) {
    _health += food->getHealth();

    response = _name + " ate " + food->getName() + " for " +
               std::to_string(food->getHealth()) + " health points";

    // remove item from owner's vector and delete
    std::visit([item](auto&& owner) { owner->removeItem(item); },
               item->getOwner().value());
    delete item;
  }

  return response;
}

int Creature::getHealth() { return _health; }

void Creature::hurt(int damage) {
  _health = _health - damage;

  if (!isAlive()) {
    _setDescription(_name + " is dead");
    for (Item* item : _inventory) {
      _currentRoom->addItem(item);
    }
  }
}

bool Creature::isAlive() { return _health > 0; }

std::vector<Item*> Creature::getInventory() { return _inventory; }

std::string Creature::attack(Creature* creature, Item* item) {
  std::string response;

  if (Weapon* s = dynamic_cast<Weapon*>(item)) {
    int damage = 0;
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(1, 10);
    damage = distribution(randomDevice) * s->getDamage();
    creature->hurt(damage);
    response += "In retaliation " + this->getName() + "  attacked " +
                creature->getName() + " with " + item->getName() + " for " +
                std::to_string(damage) + " points of damage";
  }

  return response;
}
std::string Creature::attack(Creature* creature) {
  std::string response;
  int damage = 0;

  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::uniform_int_distribution<> distribution(1, 10);

  for (const Item* item : _inventory) {
    auto iterator =
        std::find_if(_inventory.begin(), _inventory.end(),
                     [](Item* item) { return dynamic_cast<Weapon*>(item); });

    if (iterator != _inventory.end()) {
      Weapon* w = dynamic_cast<Weapon*>(*iterator);
      damage = distribution(randomDevice) * w->getDamage();
      creature->hurt(damage);
      return "In retaliation " + this->getName() + "  attacked " +
             creature->getName() + " with " + item->getName() + " for " +
             std::to_string(damage) + " points of damage";
    }
  }

  damage = distribution(randomDevice);
  creature->hurt(damage);

  response += "In retaliation " + this->getName() + " attacked " +
              creature->getName() + " with bare hands for " +
              std::to_string(damage) + " points of damage";

  return response;
}
