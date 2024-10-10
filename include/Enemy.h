//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <string>
#include <vector>

#include "Creature.h"
#include "Weapon.h"

#ifndef INCLUDE_ENEMY_H_
#define INCLUDE_ENEMY_H_

class Enemy : public Creature {
 public:
  Enemy(const std::string& name, int health, const std::string& desc)
      : Creature(name, health, desc) {}

  std::string getType() const override { return "Enemy"; }

  std::string attack(Creature* creature, Weapon* weapon);
};

#endif  // INCLUDE_ENEMY_H_
