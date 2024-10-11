//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include "../include/RestrictedRoom.h"

bool RestrictedRoom::isAccessable() { return !_boss->isAlive(); }
