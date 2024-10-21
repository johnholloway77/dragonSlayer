//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos
//

#ifndef INCLUDE_RESTRICTEDROOM_H_
#define INCLUDE_RESTRICTEDROOM_H_

#include <string>

#include "Enemy.h"

/**
 * @class RestrictedRoom RestrictedRoom.h "RestrictedRoom.h"
 * @brief A special type of room that is inaccessible to the player until a
 * designated boss enemy is dead
 */
class RestrictedRoom : public Room {
 private:
  Enemy *_boss = nullptr;

 public:
  /**
   * @brief A constructor for the restricted room that only takes in the room's
   * name, but not an enemy or a boss. Will always be inaccessible and basically
   * was made for testing
   * @param name The name of the restricted room
   */
  explicit RestrictedRoom(const std::string &name) : Room(name) {
    _accessable = false;
  }

  /**
   * @brief A constructor for restricted room that is actually useful! This
   * restricted room constructor will use a pointer to an enemy to determine if
   * a is accessible or not. Room will only be accessible if specified enemy is
   * not alive
   * @param name A const reference for the name of the restricted room
   * @param accessable A bool indicating whether or not the room is accessible
   * to the player
   * @param desc A const reference for the description of the restricted room
   * @param boss A pointer to the enemy object that will be checked before
   * accessability is determined
   */
  RestrictedRoom(const std::string &name, bool accessable,
                 const std::string &desc, Enemy *boss)
      : Room(name, accessable, desc) {
    _boss = boss;
  }

  /**
   * @brief A function to check whether or not the room is accessible.
   * Accessibility is determined by whether or not the creature passed in the
   * constructor arguments is alive or if it is dead. Room is only accessible if
   * creature is dead
   * @return A bool indicating whether or not room is accessable
   */
  bool isAccessable() override;
};

#endif  // INCLUDE_RESTRICTEDROOM_H_
