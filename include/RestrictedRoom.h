//
// Created by jholloway on 10/11/24.
//

#ifndef DRAGONSLAYER_INCLUDE_RESTRICTEDROOM_H_
#define DRAGONSLAYER_INCLUDE_RESTRICTEDROOM_H_

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

#endif  // DRAGONSLAYER_INCLUDE_RESTRICTEDROOM_H_
