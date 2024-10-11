//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos".
//

#ifndef INCLUDE_EXITROOM_H_
#define INCLUDE_EXITROOM_H_

#include "Game.h"
#include "Room.h"
class ExitRoom : public Room {
 private:
 public:
  ExitRoom(const std::string& name, const std::string& desc)
      : Room(name, desc) {}
};

#endif  // INCLUDE_EXITROOM_H_
