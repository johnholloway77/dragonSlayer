//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_WEAPON_H_
#define INCLUDE_WEAPON_H_

#include <string>

#include "Item.h"

/**
 * @class Weapon Weapon.h "Weapon.h"
 * @brief Weapon objects extend item. They are used by players and creatures to
 * inflict more damage when hurting other creatures
 */
class Weapon : public Item {
 private:
  int _damage = 5;  // default damage
 public:
  /**
   * @brief A function that specifies the type of Item object
   * @return A string specifying that this is a "Weapon"
   */
  std::string getType() const override { return "Weapon"; }

  /**
   * @brief A constructor for a weapon object. Uses the default value for
   * damage. Will leave _description as an empty string
   * @param name A const reference to a string for the name
   */
  explicit Weapon(const std::string& name) : Item(name) {}
  /**
   * @brief A Constructor for weapon objects that sets the name and a
   * description. Will set the value of _name and _description variables. Will
   * use the default value for damange
   * @param name A const reference to a string for name
   * @param desc A const reference to a string for description
   */
  Weapon(const std::string& name, const std::string& desc) : Item(name, desc) {}
  /**
   * @brief A Constructor for weapon objects that sets the name,a
   * description, and a specific damnage amount. Will set the value of _name and
   * _description variables.
   * @param name A const reference to a string for name
   * @param desc A const reference to a string for description
   * @param damage An int that will update the object's damnage variable
   */
  Weapon(const std::string& name, const std::string& desc, int damage)
      : Item(name, desc) {
    _damage = damage;
  }

  /**
   * @brief A function to get the amount of damange
   * @return An int representing _damage
   */
  int getDamage();
};

#endif  // INCLUDE_WEAPON_H_
