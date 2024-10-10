
#include "include/Game.h"
#include "include/Player.h"

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

  while (game.getCommand() != -1) {
  }

  return 0;
}
