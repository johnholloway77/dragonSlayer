//
// Created by jholloway on 10/7/24.
//

#include "../include/Enemy.h"

#include <iostream>
#include <random>
#include <string>

std::string Enemy::attack(Creature* creature, Weapon* weapon) {
  std::string response;
  int damage = 0;

  if (Weapon* s = dynamic_cast<Weapon*>(weapon)) {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(1, 10);
    damage = distribution(randomDevice) * s->getDamage();
    creature->hurt(damage);
    response += creature->getName() + " was attacked with " +
                weapon->getName() + " for " + std::to_string(damage) +
                " points of damage";

  } else {
    response += weapon->getName() + " is not a weapon\n";
    response += creature->getName() + " was attacked with " +
                weapon->getName() + " for " + std::to_string(damage) +
                " points of damage";
  }

  return response;
}
