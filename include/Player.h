//
// Created by jholloway on 10/6/24.
//

#include <vector>

#include "Creature.h"
#include "Item.h"

#ifndef DRAGONSLAYER_PLAYER_H
#define DRAGONSLAYER_PLAYER_H

class Player : public Creature {
 public:
  Player(const std::string& name, int health) : Creature(name, health){};
  Player(const std::string& name, int health, const std::string& desc)
      : Creature(name, health, desc){};

  std::string getType() const override { return "Player"; }

  std::string listInventory();

  std::string attack();
  std::string attack(Creature* creature) override;
  std::string attack(Creature* creature, Item* item) override;

  ~Player(){};
};

#endif  // DRAGONSLAYER_PLAYER_H
