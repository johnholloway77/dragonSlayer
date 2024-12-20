//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include "../include/Player.h"

#include <iostream>
#include <random>
#include <string>

#include "../include/Item.h"
#include "../include/Weapon.h"

std::string Player::listInventory() {
  std::string response = getName() + " has the following items\n";
  for (const Item* item : _inventory) {
    response += "- " + item->getName() + " Type: " + item->getType() + "\n";
    response +=
        "\t" +
        (item->getDescription().empty() ? "Nothing is known about this item"
                                        : item->getDescription()) +
        "\n";
  }
  return response;
}

std::string Player::attack() {
  return "You attack at nothing and look like a fool!";
}

std::string Player::attack(Creature* creature) {
  if (!creature->isAlive()) {
    return "You cannot hurt " + creature->getName() + " as it's already dead";
  }

  std::string response;
  int damage;
  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::uniform_int_distribution<> distribution(1, 10);
  damage = distribution(randomDevice);
  creature->hurt(damage);

  response += creature->getName() + " was attacked with bare hands for " +
              std::to_string(damage) + " points of damage";

  if (!creature->isAlive()) {
    return response + "\nYou killed " + creature->getName() +
           " with bare hands!" + ". Their body and goods fall to the ground.";
  }

  // code for enemy retaliation

  response += +"\n" + creature->attack(this);

  return response;
}

std::string Player::attack(Creature* creature, Item* item) {
  std::string response;
  int damage = 0;

  if (!creature->isAlive()) {
    return "You cannot hurt " + creature->getName() + " as it's already dead";
  }

  if (Weapon* s = dynamic_cast<Weapon*>(item)) {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(1, 10);
    damage = distribution(randomDevice) * s->getDamage();
    creature->hurt(damage);
    response += creature->getName() + " was attacked with " + item->getName() +
                " for " + std::to_string(damage) + " points of damage";

    if (!creature->isAlive()) {
      return response + "\nYou killed " + creature->getName() + " with " +
             item->getName() + ". Their body and goods fall to the ground.";
    }

    // code for enemy retaliation
    response += +"\n" + creature->attack(this);

  } else {
    response += item->getName() + " is not a weapon\n";
    response += creature->getName() + " was attacked with " + item->getName() +
                " for " + std::to_string(damage) + " points of damage";

    // code for enemy retaliation
    response += +"\n" + creature->attack(this);
  }

  return response;
}
