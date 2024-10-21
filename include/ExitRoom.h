//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos".
//

#ifndef INCLUDE_EXITROOM_H_
#define INCLUDE_EXITROOM_H_
#include <string>

#include "Game.h"
#include "Room.h"
/**
 * @class ExitRoom ExitRoom.h "ExitRoom.h"
 * @brief A special type of room object that is designated as an exit room. Used
 * to end the game and display a congrats page when loaded
 */
class ExitRoom : public Room {
 private:
 public:
  /**
   * @brief A constructor for the exit room
   * @param name A const reference for the name of the exit room
   * @param desc  A const reference for the description of the exit room
   */
  ExitRoom(const std::string& name, const std::string& desc)
      : Room(name, desc) {}
};

#endif  // INCLUDE_EXITROOM_H_
