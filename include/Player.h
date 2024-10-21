//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <string>
#include <vector>

#include "Creature.h"
#include "Item.h"

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_
/**
 *  @class Player Player.h "Player.h"
 *  @brief Class for a player object. Class extends Creature object
 */
class Player : public Creature {
 public:
  /**
   * @brief A constructor for a player object
   * @param name The name of the player
   * @param health The beginning health value of the player
   */
  Player(const std::string& name, int health) : Creature(name, health) {}

  /**
   * @brief A constructor for a player object
   * @param name The name of the player
   * @param health The beginning health value of the player
   * @param desc The description of the player
   */
  Player(const std::string& name, int health, const std::string& desc)
      : Creature(name, health, desc) {}

  /**
   * @brief an identifier for what type of creature this object is
   * @return A string value explaining the type of creature object
   */
  std::string getType() const override { return "Player"; }

  /**
   *
   * @return A string object that lists the names and description of the
   * items in the player's _inventory object
   */
  std::string listInventory();

  /**
   * @brief An attack function to be used when a player tries to attack without
   * specifying a target or a weapon
   * @return returns a string describing the failed attack
   */
  std::string attack();

  /**
   * @brief An attack function to be used when a player tries to attack a
   * specific enemy, but does not specify a weapon/item to use. Will result in
   * bare hands attack
   * @param creature The creature object that the player is trying to attack
   * @return A string describing the attack to the enemy, as well as how much
   * damage was inflicted
   */
  std::string attack(Creature* creature) override;

  /**
   * @brief An attack function to be used when the player specified a creature
   * to attack and an item with which to attack it. The function will check the
   * type of object being used in the attack. If it is a weapon it will inflict
   * damage appropriately. If not a weapon, damage will be 0 and the attack
   * ineffective
   * @param creature The creature object that the player is trying to attack
   * @param item
   * @return A string describing the attack to the enemy, as well as how much
   * damage was inflicted
   */
  std::string attack(Creature* creature, Item* item) override;
};

#endif  // INCLUDE_PLAYER_H_
