//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include "../include/RestrictedRoom.h"

bool RestrictedRoom::isAccessable() {
  if (_boss) {
    return !_boss->isAlive();
  } else {
    return false;
  }
}
