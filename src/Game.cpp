//
// Created by jholloway on 10/7/24.
//

#include "../include/Game.h"

#include <ncurses.h>

#include <iostream>
#include <sstream>

#include "../include/Enemy.h"
#include "../include/Food.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Text.h"
#include "../include/Weapon.h"

Game::Game() {
  std::cout << "\033[?1049h";
  fflush(stdout);

  // setlocale(LC_ALL, "");
  setlocale(LC_ALL, "C.UTF-8");

  initscr();
  cbreak();
  // noecho();
  keypad(stdscr, TRUE);

  getmaxyx(stdscr, _screen_height, _screen_width);
  _input_height = _screen_height / 5;
  _display_height = _screen_height - _input_height;

  loadTitle();

  _display_win = newwin(_display_height, _screen_width, 0, 0);
  _input_win = newwin(_input_height, _screen_width, _display_height, 0);
  delwin(_title_win);

  scrollok(_display_win, true);
  // box(display_win, 0, 0);
  box(_input_win, 0, 0);
  wrefresh(_display_win);
  wrefresh(_input_win);

  // Do I even need these anymore?
  _input_win_width = _screen_width - 2;
  _display_win_width = _screen_width - 2;
}

Game::~Game() {
  delete _player;

  for (Room *room : _rooms) {
    delete room;
  }

  endwin();
  printf("\033[?1049l");
  std::cout << "\nText game successfully exited" << std::endl;
}

int Game::setDefaults() {
  _currentRow = 1;
  _inputText = "";
  // noecho();

  return 0;
}

int Game::loadTitle() {
  curs_set(0);
  _title_win = newwin(_screen_height, _screen_width, 0, 0);

#ifdef __linux__
  mvwprintw(_title_win, 1, 1, title2.c_str());
#else
  mvwprintw(_title_win, 1, 1, title.c_str());
#endif
  wrefresh(_title_win);
  sleep(2);
  curs_set(1);

  return 0;
}

int Game::initPlayer() {
  setDefaults();
  mvwprintw(_display_win, _currentRow++, 1, "Enter your name brave warrior!");
  wrefresh(_display_win);

  mvwprintw(_input_win, 1, 1, "Name: ");
  wrefresh(_input_win);

  echo();
  wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
  _inputText = std::string(buffer);

  if (_inputText == "exit" || _inputText == "EXIT") {
    return -1;
  };

  _player = new Player(_inputText, 100, "Our lowly hero");

  return 0;
}

int Game::welcomeMessage() {
  setDefaults();
  wclear(_display_win);
  mvwprintw(_display_win, _currentRow++, 1, "Welcome %s\n",
            _player->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "%s\n", welcomeText.c_str());
  wrefresh(_display_win);

  mvwprintw(_input_win, 1, 1, "Press Enter to begin");
  wrefresh(_input_win);
  wgetnstr(_input_win, buffer, sizeof(buffer) - 1);

  return 0;
}

int Game::loadRoom(std::string roomName) {
  for (Room *room : _rooms) {
    if (room && room->getName() == roomName) {
      loadRoom(room);
      return 0;
    }
  }

  return -1;
}

int Game::loadRoom(Room *room) {
  _currentRoom = room;

  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            room->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            room->getDescription().c_str());
  // mvwprintw(_display_win, _currentRow++, 1, "Items you see:");
  // mvwprintw(_display_win, _currentRow++, 1, "%s", room->listItems().c_str());
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);

  return 0;
}

int Game::getCommand() {
  echo();

  std::vector<std::string> words;
  std::string currentWord;

  wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
  int i = 0;
  while (buffer[i] != '\0') {
    buffer[i] = std::tolower(buffer[i]);
    i++;
  }

  _inputText = std::string(buffer);

  // This will check for invalid entries like '\n' or other jackassery from user
  if (_inputText.empty()) {
    invalidCommand(_inputText, _currentRoom);
    return 0;
  }

  std::istringstream iss(_inputText);

  while (iss >> currentWord) {
    words.push_back(currentWord);
  }

  currentWord = words.front();
  words.erase(words.begin());

  if (currentWord == "exit" || currentWord == "quit" ||
      currentWord == "escape") {
    return -1;
  }

  if (currentWord == "look") {
    if (!words.empty()) {
      currentWord = words.front();
      words.erase(words.begin());

      if (currentWord == "at") {
        if (!words.empty()) {
          currentWord = words.front();
          words.erase(words.begin());

          /*
           * Need to create something to search through Room's creatures and
           * items Call the appropriate look method.
           *
           */
          for (Creature *creature : _currentRoom->getCreatures()) {
            if (currentWord == _toLower(creature->getName())) {
              look(creature);
              return 0;
            }
          }

          for (Item *item : _currentRoom->getInventory()) {
            if (currentWord == _toLower(item->getName())) {
              look(item);
              return 0;
            }
          }

          invalidCommand(_inputText, _currentRoom);
        } else {
          lookAtWhat();
        }
      } else {
        if (currentWord == "north") {
          look("north");
        } else if (currentWord == "east") {
          look("east");
        } else if (currentWord == "south") {
          look("south");
        } else if (currentWord == "west") {
          look("west");
        } else if (currentWord == "inventory" || currentWord == "player") {
          look(_player);
        } else {
          lookAtWhat();
        }
      }
    } else {
      look(_currentRoom);
    }
    return 0;
  } else if (currentWord == "go") {
    if (!words.empty()) {
      currentWord = words.front();
      words.erase(words.begin());

      if (currentWord == "north") {
        if (_currentRoom->getNorth()) {
          go(_currentRoom->getNorth());
        } else {
          go(currentWord);
        }

      } else if (currentWord == "east") {
        if (_currentRoom->getEast()) {
          go(_currentRoom->getEast());
        } else {
          go(currentWord);
        }
      } else if (currentWord == "south") {
        if (_currentRoom->getSouth()) {
          go(_currentRoom->getSouth());
        } else {
          go(currentWord);
        }
      } else if (currentWord == "west") {
        if (_currentRoom->getWest()) {
          go(_currentRoom->getWest());
        } else {
          go(currentWord);
        }
      } else {
        go();
      }
    }
  } else if (currentWord == "help") {
    helpScreen();
  } else if (currentWord == "pickup" || currentWord == "get" || currentWord == "pick-up" || currentWord == "grab") {
    //fill out this section
    if (!words.empty()) {
      currentWord = words.front();
      words.erase(words.begin());

      for (Item *item : _currentRoom->getInventory()) {
        if (currentWord == _toLower(item->getName())) {
          _player->addItem(item);
          return loadRoom(_currentRoom, 'p', item);
        }
      }

    } else {
      invalidCommand(_inputText, _currentRoom);
      return 0;
    }
  } else {
    invalidCommand(_inputText, _currentRoom);
  }

  return 0;
}


//int Game::getCommand() {
//  echo();
//
//  std::vector<std::string> words;
//  std::string currentWord;
//
//  wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
//  int i = 0;
//  while (buffer[i] != '\0') {
//    buffer[i] = std::tolower(buffer[i]);
//    i++;
//  }
//
//  _inputText = std::string(buffer);
//
//  // This will check for invalid entries like '\n' or other jackassery from user
//  if (_inputText.empty()) {
//    invalidCommand(_inputText, _currentRoom);
//    return 0;
//  }
//
//  std::istringstream iss(_inputText);
//
//  while (iss >> currentWord) {
//    words.push_back(currentWord);
//  }
//
//  currentWord = words.front();
//  words.erase(words.begin());
//
//  if (currentWord == "exit" || currentWord == "quit" ||
//      currentWord == "escape") {
//    return -1;
//  }
//
//  if (currentWord == "look") {
//    if (!words.empty()) {
//      currentWord = words.front();
//      words.erase(words.begin());
//
//      if (currentWord == "at") {
//        if (!words.empty()) {
//          currentWord = words.front();
//          words.erase(words.begin());
//
//          /*
//           * Need to create something to search through Room's creatures and
//           * items Call the appropriate look method.
//           *
//           */
//          for (Creature *creature : _currentRoom->getCreatures()) {
//            if (currentWord == _toLower(creature->getName())) {
//              look(creature);
//              return 0;
//            }
//          }
//
//          for (Item *item : _currentRoom->getInventory()) {
//            if (currentWord == _toLower(item->getName())) {
//              look(item);
//              return 0;
//            }
//          }
//
//          invalidCommand(_inputText, _currentRoom);
//        }
//
//        lookAtWhat();
//
//}
//      } else {
//        if (currentWord == "north") {
//          look("north");
//        } else if (currentWord == "east") {
//          look("east");
//        } else if (currentWord == "south") {
//          look("south");
//        } else if (currentWord == "west") {
//          look("west");
//        } else if (currentWord == "inventory" || currentWord == "player") {
//          look(_player);
//
//        } else {
//          lookAtWhat();
//        }
//        }
//      }
//    }
//
//  } else {
//    look(_currentRoom);
//  }
//
//    return 0;
//  } else if (currentWord == "go") {
//    if (!words.empty()) {
//      currentWord = words.front();
//      words.erase(words.begin());
//
//      if (currentWord == "north") {
//        if (_currentRoom->getNorth()) {
//          go(_currentRoom->getNorth());
//        } else {
//          go(currentWord);
//        }
//
//      } else if (currentWord == "east") {
//        if (_currentRoom->getEast()) {
//          go(_currentRoom->getEast());
//        } else {
//          go(currentWord);
//        }
//      } else if (currentWord == "south") {
//        if (_currentRoom->getSouth()) {
//          go(_currentRoom->getSouth());
//        } else {
//          go(currentWord);
//        }
//      } else if (currentWord == "west") {
//        if (_currentRoom->getWest()) {
//          go(_currentRoom->getWest());
//        } else {
//          go(currentWord);
//        }
//      } else {
//        go();
//      }
//    }
//
//  } else if (currentWord == "help") {
//    helpScreen();
//  } else if(currentWord == "pickup" || currentWord == "get" || currentWord == "pick-up" || currentWord == "grab"){
//    //fill out this section
//    if (!words.empty()) {
//      currentWord = words.front();
//      words.erase(words.begin());
//
//      for(Item *item : _currentRoom->getInventory()){
//        if(currentWord == _toLower(item->getName())){
//          _player->addItem(item);
//          return loadRoom(_currentRoom, 'p', item );
//        }
//      }
//
//    } else{
//      invalidCommand(_inputText, _currentRoom);
//      return 0;
//    }
//  } else {
//    invalidCommand(_inputText, _currentRoom);
//  }
//
//  return 0;
//}

int Game::invalidCommand(std::string cmd, Room *room) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Sorry,");
  mvwprintw(_display_win, _currentRow++, 1, "I don't understand: %s",
            cmd.c_str());
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            room->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            room->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
  return 0;
}

int Game::initWorldMap() {
  Room *home = new Room(
      "Home",
      "You are outside of your thatched roof cottage. The top of the roof"
      " is smoking from a recent dragon attack. Ironically you were preparing "
      "food at the"
      " time, so you won't have to bake it yourself."
      " As a peasant your cannot afford to build a new roof"
      "\n\nCould be worse...at least you don't have student loans");
  Food *muffin = new Food("muffin");
  home->addItem(muffin);

  Room *field = new Room(
      "Field",
      "You are in a field where you see the charred remains of fallen"
      " knights from the dragon attack. Some are still smoking with a odd "
      "smell."
      " You find yourself getting hungry at the smell, but remind yourself "
      "that you are"
      " better than that. Plus you think it will give you an upset tummy.");
  Food *humanMeat = new Food("humanMeat", "Forbidden barbequed meat", 15);
  field->addItem(humanMeat);
  Weapon *speer = new Weapon(
      "speer", "An old speer from fallen knight. Has burn marks", 10);
  field->addItem(speer);

  Room *rockyArea =
      new Room("Rocky Area",
               "You come to a rocky plateau. The wind carries the scent of"
               " death as its cold blow surrounds you. It is the plateau of "
               "the Dark Knight."
               " The fearsome brute who haunts the trails of the land.");
  Enemy *darkKnight = new Enemy("DarkKnight", 50, R"(This guy is a jerk)");
  rockyArea->addCreature(darkKnight);

  // basically creating a linked list of rooms
  home->setEast(field);
  field->setEast(rockyArea);

  _rooms.push_back(home);
  _rooms.push_back(field);
  _rooms.push_back(rockyArea);

  return 0;
}

void Game::look(Player* player) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Our hero: %s",
            player->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Current Location: %s",
            _currentRoom->getName().c_str());

  // This is a temp thing until I make text display line by line.
  _currentRow++;

  mvwprintw(_display_win, _currentRow++, 1, "%s",
            player->listInventory().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::look(std::string dir) {
  Room *room;

  if (dir == "north") {
    room = _currentRoom->getNorth();
  } else if (dir == "east") {
    room = _currentRoom->getEast();
  } else if (dir == "south") {
    room = _currentRoom->getSouth();
  } else if (dir == "west") {
    room = _currentRoom->getWest();
  } else {
    room = nullptr;
  }

  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "You look to the distance:");
  if (!room) {
    mvwprintw(_display_win, _currentRow++, 1,
              "There is nothing in that direction");
  } else {
    mvwprintw(_display_win, _currentRow++, 1, "You see %s",
              room->getName().c_str());
  }
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::look(Room *room) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            room->getName().c_str());

  // This is a temp thing until I make text display line by line.
  _currentRow = _currentRow + 2;

  mvwprintw(_display_win, _currentRow++, 1, "In this area stands");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            room->listCreatures().c_str());

  // This is a temp thing until I make text display line by line.
  _currentRow = _currentRow + 5;

  mvwprintw(_display_win, _currentRow++, 1, "Items you see:");
  mvwprintw(_display_win, _currentRow++, 1, "%s", room->listItems().c_str());
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);

  return;
}

void Game::look(Creature *creature) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "You look at %s",
            creature->getName().c_str());
  if (creature->getDescription().empty()) {
    mvwprintw(_display_win, _currentRow++, 1, "You learn nothing from looking");
  } else {
    mvwprintw(_display_win, _currentRow++, 1, "%s",
              creature->getDescription().c_str());
  }
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::look(Item *item) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "You look at %s",
            item->getName().c_str());
  if (item->getDescription().empty()) {
    mvwprintw(_display_win, _currentRow++, 1, "You learn nothing from looking at %s", item->getName().c_str());
  } else {
    mvwprintw(_display_win, _currentRow++, 1, "%s",
              item->getDescription().c_str());
  }
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::lookAtWhat() {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "look at what?");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            _currentRoom->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
};

void Game::go() {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Go which direction?");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            _currentRoom->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::go(std::string dir) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "You cannot go %s", dir.c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Try a different direction");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            _currentRoom->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::go(Room *room) { loadRoom(room); }

//
// void Game::look(Item *item) {
//
//}

void Game::helpScreen() {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Commands - Enter the following");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "\"exit\" or \"quit\" to end game");

  mvwprintw(_display_win, _currentRow++, 1, "\"look\" - look in a direction");
  mvwprintw(_display_win, _currentRow++, 1,
            "\tlook in a direction: eg \"look west\"");
  mvwprintw(_display_win, _currentRow++, 1,
            "\tlook in a item or creature: eg \"look at DarkKnight\"");

  mvwprintw(_display_win, _currentRow++, 1, "\"go\" - go in a direction");
  mvwprintw(_display_win, _currentRow++, 1, "\t eg: go west");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1,
            "I'll add some more if once implemented - John");

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}
int Game::loadRoom(Room *room, char c, Item *item) {

  std::string actionString;

  if(c == 'p'){
    actionString = "picks up";
  } else if(c == 'c'){
    actionString = "drops";
  } else{
    actionString = "does something with";
  }

  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Player %s %s.", actionString.c_str(), item->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            _currentRoom->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);


  return 0; }
