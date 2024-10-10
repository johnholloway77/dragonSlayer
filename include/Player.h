//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <string>
#include <vector>

#include "Creature.h"
#include "Item.h"

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_

class Player : public Creature {
 public:
  Player(const std::string& name, int health) : Creature(name, health) {}
  Player(const std::string& name, int health, const std::string& desc)
      : Creature(name, health, desc) {}

  std::string getType() const override { return "Player"; }

  std::string listInventory();

  std::string attack();
  std::string attack(Creature* creature) override;
  std::string attack(Creature* creature, Item* item) override;
};

#endif  // INCLUDE_PLAYER_H_
