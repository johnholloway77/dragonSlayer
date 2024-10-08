//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_WEAPON_H
#define DRAGONSLAYER_WEAPON_H

#include "Item.h"

class Weapon : public Item {
 private:
  int _damage = 5;  // default damage
 public:
  std::string getType() const override { return "Weapon"; }

  Weapon(const std::string& name) : Item(name){};
  Weapon(const std::string& name, const std::string& desc) : Item(name, desc){};
  Weapon(const std::string& name, const std::string& desc, int damage)
      : Item(name, desc) {
    _damage = damage;
  };

  int getDamage();
};

#endif  // DRAGONSLAYER_WEAPON_H
