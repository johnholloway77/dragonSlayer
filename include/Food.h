//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_FOOD_H_
#define INCLUDE_FOOD_H_

#include <string>

#include "Item.h"

/**
 * @class Food Food.h "Food.h"
 * @brief Food extends item objects. Can be used by the player to try to attack
 * a creature, or be used by the player to increase/decrease player health
 */
class Food : public Item {
 private:
  int _health = 10;  // default health recoup.

 public:
  /**
   * @brief A function that specifies the type of Item object
   * @return A string specifying that this is a "Food" object
   */
  std::string getType() const override { return "Food"; }

  /**
   * @brief A function to get the value of _health. Health, positive or
   * negative, will be added to the player's health when used
   * @return An int for the _health variable
   */
  int getHealth();

  /**
   * @brief A constructor that specifies the name of the food object. Leave the
   * description an empty string and uses default value for food
   * @param name A const reference to a string for name
   */
  explicit Food(const std::string& name) : Item(name) {}

  /**
   *@brief A constructor for food objects that lets you set the food's name and
   *description but still use default value for health
   * @param name A const reference to a string for name
   * @param desc A const reference to a string for description
   */
  Food(const std::string& name, const std::string& desc) : Item(name, desc) {}

  /**
   * @brief A constructor that lets you set the name and health, but leaves the
   * description an empty string. Useful if you want nothing to be known about
   * the mysterious food object
   * @param name A const reference to a string for name
   * @param health An int for health value
   */
  Food(const std::string& name, int health) : Item(name) { _health = health; }

  /**
   * @brief A constructor that let's you set all of the food's main values
   * @param name  A const reference to a string for name
   * @param desc  A const reference to a string for description
   * @param health An int for health value
   */
  Food(const std::string& name, const std::string& desc, int health)
      : Item(name, desc) {
    _health = health;
  }
};

#endif  // INCLUDE_FOOD_H_
