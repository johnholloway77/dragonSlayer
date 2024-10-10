//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <ncurses.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "Player.h"
#include "Room.h"

class Game {
 private:
  int _screen_height;
  int _screen_width;
  int _input_height;
  int _display_height;

  int _input_win_width;
  int _display_win_width;

  WINDOW *_title_win;
  WINDOW *_display_win;
  WINDOW *_input_win;

  Room *_currentRoom;

  char buffer[256];
  std::string _inputText;

  int _currentRow = 1;

  Player *_player = nullptr;
  std::vector<Room *> _rooms;

  std::string _toLower(const std::string &inString) {
    std::string str = inString;

    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return str;
  }

 public:
  Game();
  ~Game();

  int setDefaults();
  int loadTitle();
  int loadRoom(Room *room);
  int loadRoom(Room *room, char c, const Item *item);
  int loadRoom(const std::string &roomName);
  int initPlayer();
  int initWorldMap();
  int welcomeMessage();
  int getCommand();
  int invalidCommand(const std::string &cmd, Room *room);

  void look(Player *p);
  void look(const std::string &dir);
  void look(Room *room);
  void look(Creature *creature);
  void look(Item *item);
  void customResponse(const std::string &str);

  void go(const std::string &dir);
  void go(Room *room);

  void helpScreen();

  int deadScreen();
};

#endif  // INCLUDE_GAME_H_
