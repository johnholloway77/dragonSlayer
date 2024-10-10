//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_FOOD_H_
#define INCLUDE_FOOD_H_

#include <string>

#include "Item.h"

class Food : public Item {
 private:
  int _health = 10;  // default health recoup.

 public:
  std::string getType() const override { return "Food"; }

  int getHealth();

  explicit Food(const std::string& name) : Item(name) {}
  Food(const std::string& name, const std::string& desc) : Item(name, desc) {}
  Food(const std::string& name, int health) : Item(name) { _health = health; }
  Food(const std::string& name, const std::string& desc, int health)
      : Item(name, desc) {
    _health = health;
  }
};

#endif  // INCLUDE_FOOD_H_
