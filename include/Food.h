//
// Created by jholloway on 10/6/24.
//

#ifndef DRAGONSLAYER_FOOD_H
#define DRAGONSLAYER_FOOD_H

#include "Item.h"

class Food : public Item {
 private:
  int _health = 10;  // default health recoup.

 public:
  std::string getType() const override { return "Food"; }

  int getHealth();

  Food(const std::string& name) : Item(name){};
  Food(const std::string& name, const std::string& desc) : Item(name, desc){};
  Food(const std::string& name, int health) : Item(name) { _health = health; };
  Food(const std::string& name, const std::string& desc, int health)
      : Item(name, desc) {
    _health = health;
  };
};

#endif  // DRAGONSLAYER_FOOD_H
