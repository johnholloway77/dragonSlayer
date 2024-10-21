//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <string>
#include <vector>

#include "Creature.h"
#include "Weapon.h"

#ifndef INCLUDE_ENEMY_H_
#define INCLUDE_ENEMY_H_

/**
 * @class Enemy Enemy.h "Enemy.h"
 * @brief A class for enemy objects. Class extends abstract class creature
 */
class Enemy : public Creature {
 public:
  /**
   * @brief The constructor to be used for creating an enemy
   * @param name A string for the enemy's name
   * @param health  The starting health for the enemy
   * @param desc  A description of the enemy.
   */
  Enemy(const std::string& name, int health, const std::string& desc)
      : Creature(name, health, desc) {}

  /**
   * @brief An identifier for what type of creature this is. Specifies enemy.
   * @return a string stating "Enemy"
   */
  std::string getType() const override { return "Enemy"; }

  /**
   * @brief A function used to attack an creature (usually the player). Unlike
   * the other  attack functions, enemies can only attack with a Weapon object
   * @param creature A pointer to the creature to be attacked
   * @param weapon A pointer to the weapon being used for the attack
   * @return A string describing the attack against creature and the damage
   * inflected
   */
  std::string attack(Creature* creature, Weapon* weapon);
};

#endif  // INCLUDE_ENEMY_H_
