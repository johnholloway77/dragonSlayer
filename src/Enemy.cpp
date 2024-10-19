//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include "../include/Enemy.h"

#include <iostream>
#include <random>
#include <string>

std::string Enemy::attack(Creature* creature, Weapon* weapon) {
  std::string response;
  int damage = 0;

  std::random_device randomDevice;
  std::mt19937 gen(randomDevice());
  std::uniform_int_distribution<> distribution(1, 10);
  damage = distribution(randomDevice) * weapon->getDamage();
  creature->hurt(damage);
  response += creature->getName() + " was attacked with " + weapon->getName() +
              " for " + std::to_string(damage) + " points of damage";

  return response;
}
