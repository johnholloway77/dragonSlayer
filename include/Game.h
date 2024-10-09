//
// Created by jholloway on 10/7/24.
//

#ifndef DRAGONSLAYER_GAME_H
#define DRAGONSLAYER_GAME_H

#include <ncurses.h>
#include <unistd.h>

#include <cctype>
#include <string>

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
  bool _validInput;

  char buffer[256];
  std::string _inputText;

  int _currentRow = 1;

  Player *_player = nullptr;
  std::vector<Room *> _rooms;


  std::string _toLower(std::string inString){
   std::string str = inString;

   std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return  std::tolower(c);});

   return str;
  }

 public:
  Game();
  ~Game();

  int setDefaults();
  int loadTitle();
  int loadRoom(Room *room);
  int loadRoom(Room *room, char c, Item *item);
  int loadRoom(std::string roomName);
  int initPlayer();
  int initWorldMap();
  int welcomeMessage();
  int getCommand();
  int invalidCommand(std::string cmd, Room *room);

  void look(Player* p);
  void look(std::string dir);
  void look(Room *room);
  void look(Creature *creature);
  void look(Item *item);
  void customResponse(std::string str);


  void go(std::string dir);
  void go(Room *room);

  void helpScreen();

  int deadScreen();
};

#endif  // DRAGONSLAYER_GAME_H
