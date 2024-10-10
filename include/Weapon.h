//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_WEAPON_H_
#define INCLUDE_WEAPON_H_

#include <string>

#include "Item.h"

class Weapon : public Item {
 private:
  int _damage = 5;  // default damage
 public:
  std::string getType() const override { return "Weapon"; }

  explicit Weapon(const std::string& name) : Item(name) {}
  Weapon(const std::string& name, const std::string& desc) : Item(name, desc) {}
  Weapon(const std::string& name, const std::string& desc, int damage)
      : Item(name, desc) {
    _damage = damage;
  }

  int getDamage();
};

#endif  // INCLUDE_WEAPON_H_
