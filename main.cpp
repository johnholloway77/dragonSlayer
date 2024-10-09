#include <ncurses.h>
#include <unistd.h>

#include <cctype>
#include <iostream>

#include "include/Food.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/Room.h"
#include "include/Weapon.h"

void init() {}

int main() {
  Game game = Game();
  if (game.initPlayer() < 0) {
    // error or exit
    return -1;
  }
  game.welcomeMessage();

  if (game.initWorldMap() < 0) {
    // error or exit
    return -1;
  }
  game.loadRoom("Home");
  // game.start();

  while (game.getCommand() != -1) {
  }

  return 0;
}
