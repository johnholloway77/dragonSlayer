//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos
//

#ifndef _INCLUDE_RESTRICTEDROOM_H_
#define _INCLUDE_RESTRICTEDROOM_H_

#include <string>

#include "Enemy.h"

class RestrictedRoom : public Room {
 private:
  Enemy *_boss = nullptr;

 public:
  explicit RestrictedRoom(std::string &name) : Room(name) {
    _accessable = false;
  }
  RestrictedRoom(const std::string &name, bool accessable,
                 const std::string &desc, Enemy *boss)
      : Room(name, accessable, desc) {
    _boss = boss;
  }

  bool isAccessable() override;
};

#endif  // _INCLUDE_RESTRICTEDROOM_H_
