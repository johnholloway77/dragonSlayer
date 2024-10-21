//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_CREATURE_H_
#define INCLUDE_CREATURE_H_
#include <string>
#include <vector>

#include "Item.h"
#include "Room.h"

class Item;

/**
 * @class Creature Creature.h "Creature.h"
 *  @brief The abstract baseclass for Player and Enemy object. Creatures refer
 * to all living things in the game. Both enemy and player
 */
class Creature {
 protected:
  std::string _name;
  int _health;
  std::string _description;
  std::vector<Item*> _inventory;
  bool _alive;
  Room* _currentRoom = nullptr;

  /**
   * @brief A private descriptor. Used to update the description of the creature
   * in the event that isAlive = false
   * @param newDesc
   */
  void _setDescription(const std::string& newDesc) { _description = newDesc; }

 public:
  /**
   * @brief A constrctor for the abstract class of Creature
   * @param name The name of the creature
   * @param health The starting health of the creature
   */
  Creature(const std::string& name, int health) : _name(name), _health(health) {
    _alive = true;
  }
  /**
   * @brief Another constuctor for creature objects
   * @param name
   * @param health
   * @param desc
   */
  Creature(const std::string& name, int health, const std::string& desc)
      : _name(name), _health(health), _description(desc) {
    _alive = true;
  }

  /**
   * @brief The destructor for creature objects. It runs a loop deleting all
   * items inside of the creature's inventory when the creature is deleted to
   * avoid memory leaks
   */
  virtual ~Creature() {
    for (Item* item : _inventory) {
      delete item;
    }
  }

  /**
   * @brief A virtual method that cmust be over written by the child class. To
   * be used to return the specific type of the child creature
   * @return A string specifying the type of creature
   */
  virtual std::string getType() const = 0;
  /**
   * @brief Add an item to the private vector _inventory. This method will also
   * remove the object from the current container once it is added to this
   * creature's inventory to prevent duplicate ownership of an item
   * @param item A pointer to an item object
   */
  void addItem(Item* item);
  /**
   * @brief remove's an item from the creature's inventory vector
   * @param item A pointer to the specific item being removed from creature's
   * inventory
   */
  void removeItem(Item* item);

  /**
   * @brief A function used to identify the current room  holding the creature
   * @return A pointer to the room holding the creature
   */
  Room* getCurrentRoom();
  /**
   * @brief A function used to add the creature object to a specified room
   * @param room A pointer to a room object. If creature is not assigned to a
   * room, nullptr is returns
   */
  void setCurrentRoom(Room* room);

  /**
   * @brief A function to get the name of the creature
   * @return The string value of _name. If _name is null, then the string
   * "Name_Not+Provided" is return
   */
  std::string getName();

  /**
   * @brief A function to get the description of the creature
   * @return A reference to the _description string
   */
  const std::string& getDescription();

  /**
   * @brief A function to consume an item. If the item is food the item is con
   * consumed, _health of the creature is updated, the item is then removed from
   * _inventory vector and deleted. If not food, player is told they can't use
   * the item in this way
   * @param item A pointer to an item object
   * @return A string informing the player that the creature either ate  the
   * food object and health updated, or a string informing that they can't use
   * the object in this way
   */
  std::string useItem(Item* item);

  /**
   * @brief A function to get the health of the creature
   * @return An int representing the creature's current _health at time of call
   */
  int getHealth();

  /**
   * @brief A function used to inflict damanage upon a creature. Will update
   * _health, check if creature is still alive. If not, function will either
   * check if the dead creature is a player object. If the creature is not the
   * player, the items in the creature's _inventory are removed and added to
   * that of the room containing the creature
   * @param damage An int representing the damage to be inflicted upon enemy
   */
  void hurt(int damage);

  /**
   * @brief Checks if the creature's health is equal to or below zero to
   * determine if they're alive or not
   * @return a bool representing if _health > 0 is true or false
   */
  bool isAlive();

  /**
   * @brief An attack function to be used when the creature attacks another
   * creature using an item. Will be used to determine an amount of damage to
   * inflict and pass that value to the hurt method of the target
   * @param creature A pointer to a creature object that this creature is trying
   * to attack
   * @param item The item object with which the creature is going to attack
   * @return A string describing the attack
   */
  virtual std::string attack(Creature* creature, Item* item);

  /**
   * @brief An attack function to be used when the creature attacks another
   * creature without using an item. Will be used to determine an amount of
   * damage to inflict and pass that value to the hurt method of the target
   * @param creature A pointer to a creature object that this creature is trying
   * to attack
   * @return A string describing the attack
   */
  virtual std::string attack(Creature* creature);

  /**
   * @brief A function to get a reference to the creature's inventory. Useful
   * for looking at inventory
   * @return A reference to _inventory
   */
  const std::vector<Item*>& getInventory();
};

#endif  // INCLUDE_CREATURE_H_
