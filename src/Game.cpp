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
#include "../include/Text.h"

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

  initPlayer();
  welcomeMessage();
  initWorldMap();
  loadRoom("Home");
  while (getCommand() != -1) {
  }
}

Game::~Game() {
  delete _player;

  for (Room *room : _rooms) {
    delete room;
  }

  endwin();
  printf("\033[?1049l");
  std::cout << "\nDragonSlayer successfully exited" << std::endl;
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
  }

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
  noecho();
  wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
  echo();

  return 0;
}

int Game::loadRoom(const std::string &roomName) {
  auto tempRooms = _rooms;
  auto iterator = std::find_if(
      tempRooms.begin(), tempRooms.end(), [&roomName, this](Room *room) {
        return room && _toLower(roomName) == _toLower(room->getName());
      });
  if (iterator != tempRooms.end()) {
    loadRoom(*iterator);
    return 0;
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

  if (_player->isAlive()) {
    if (currentWord == "look") {
      if (!words.empty()) {
        currentWord = words.front();
        words.erase(words.begin());

        if (currentWord == "at") {
          if (!words.empty()) {
            currentWord = words.front();
            words.erase(words.begin());

            auto tempRoomCreatures = _currentRoom->getCreatures();
            auto iteratorCreature = std::find_if(
                tempRoomCreatures.begin(), tempRoomCreatures.end(),
                [&currentWord, this](Creature *creature) {
                  return currentWord == _toLower(creature->getName());
                });

            if (iteratorCreature != tempRoomCreatures.end()) {
              look(*iteratorCreature);
              return 0;
            }

            auto tempRoomInventory = _currentRoom->getInventory();
            auto iterator =
                std::find_if(tempRoomInventory.begin(), tempRoomInventory.end(),
                             [&currentWord, this](const Item *item) {
                               return currentWord == _toLower(item->getName());
                             });

            if (iterator != tempRoomInventory.end()) {
              look(*iterator);
              return 0;
            }

            invalidCommand(_inputText, _currentRoom);
          } else {
            customResponse("Look at what?");
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
            customResponse("Look at what?");
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
          customResponse("Go which direction?");
        }
      }
    } else if (currentWord == "help") {
      helpScreen();
    } else if (currentWord == "pickup" || currentWord == "get" ||
               currentWord == "pick-up" || currentWord == "grab") {
      // fill out this section
      if (!words.empty()) {
        currentWord = words.front();
        words.erase(words.begin());

        auto tempRoomInventory = _currentRoom->getInventory();
        auto iterator =
            std::find_if(tempRoomInventory.begin(), tempRoomInventory.end(),
                         [&currentWord, this](const Item *item) {
                           return currentWord == _toLower(item->getName());
                         });

        if (iterator != tempRoomInventory.end()) {
          _player->addItem(*iterator);
          return loadRoom(_currentRoom, 'p', *iterator);
        }

        customResponse("Pickup what?");

      } else {
        invalidCommand(_inputText, _currentRoom);
        return 0;
      }
    } else if (currentWord == "eat" || currentWord == "consume") {
      if (!words.empty()) {
        currentWord = words.front();
        words.erase(words.begin());

        auto tempPlayerInventory = _player->getInventory();

        auto iteratorPlayerInventory =
            std::find_if(tempPlayerInventory.begin(), tempPlayerInventory.end(),
                         [&currentWord, this](const Item *item) {
                           return currentWord == _toLower(item->getName());
                         });

        if (iteratorPlayerInventory != tempPlayerInventory.end()) {
          customResponse(_player->useItem(*iteratorPlayerInventory));

          return 0;
        }

        /// This response will occur only if the player doesn't have the item in
        /// their inventory
        auto tempRoomInventory = _currentRoom->getInventory();

        auto iterator =
            std::find_if(tempRoomInventory.begin(), tempRoomInventory.end(),
                         [&currentWord, this](const Item *item) {
                           return currentWord == _toLower(item->getName());
                         });

        if (iterator != tempRoomInventory.end()) {
          customResponse("You cannot eat " + (*iterator)->getName() +
                         " unless you pick it up first");

          return 0;
        }
      }
      customResponse("Eat what?");
    } else if (currentWord == "attack" || currentWord == "hit" ||
               currentWord == "hurt") {
      if (!words.empty()) {
        currentWord = words.front();
        words.erase(words.begin());

        for (Creature *creature : _currentRoom->getCreatures()) {
          if (currentWord == _toLower(creature->getName())) {
            if (!words.empty()) {
              currentWord = words.front();
              words.erase(words.begin());

              if (currentWord == "with" || currentWord == "using") {
                if (!words.empty()) {
                  currentWord = words.front();
                  words.erase(words.begin());

                  auto tempInventory = _player->getInventory();

                  auto iterator = std::find_if(
                      tempInventory.begin(), tempInventory.end(),
                      [&currentWord, this](const Item *item) {
                        return currentWord == _toLower(item->getName());
                      });

                  if (iterator != tempInventory.end()) {
                    customResponse(_player->attack(creature, *iterator));
                    return 0;
                  }
                }

                customResponse("attack " + creature->getName() + " with what?");
                return 0;
              }
            }

            customResponse(_player->attack(creature));
            return 0;
          }
        }

        if (currentWord == "player" ||
            currentWord == _toLower(_player->getName())) {
          if (!words.empty()) {
            currentWord = words.front();
            words.erase(words.begin());

            if (currentWord == "with" || currentWord == "using") {
              if (!words.empty()) {
                currentWord = words.front();
                words.erase(words.begin());

                auto tempInventory = _player->getInventory();

                auto iterator = std::find_if(
                    tempInventory.begin(), tempInventory.end(),
                    [&currentWord, this](const Item *item) {
                      return currentWord == _toLower(item->getName());
                    });

                if (iterator != tempInventory.end()) {
                  customResponse("self injury! " +
                                 _player->attack(_player, *iterator));
                  return 0;
                }
              }

              customResponse("attack " + _player->getName() + " with what?");
              return 0;
            }
          }

          customResponse("Self-injury! " + _player->attack(_player));
          return 0;
        }
      }

      customResponse("Attack who?");

    } else {
      invalidCommand(_inputText, _currentRoom);
    }

  } else {
    deadScreen();
  }
  return 0;
}

int Game::invalidCommand(const std::string &cmd, Room *room) {
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
  /*
   * The first area on the map
   *
   */
  Room *home = new Room(
      "Home",
      " You are outside of your thatched roof cottage. The top of the roof"
      " is smoking from a recent dragon attack. Ironically you were preparing "
      " food at the"
      " time, so you won't have to bake it yourself."
      " As a peasant your cannot afford to build a new roof"
      "\n\n Could be worse...at least you don't have student loans"
      "\n\n The trail in front goes South and East");
  Food *muffin = new Food("muffin");
  home->addItem(muffin);
  /*
   *  The second area on the map
   */
  Room *field = new Room(
      "Field",
      " You are in a field where you see the charred remains of fallen"
      " knights from the dragon attack. Some are still smoking with a odd "
      " smell."
      " You find yourself getting hungry at the smell, but remind yourself "
      " that you are"
      " better than that. Plus you think it will give you an upset tummy."
      "\n\n The trail in front goes West and East");
  Food *humanMeat = new Food("humanMeat", "Forbidden barbequed meat", -1000);
  field->addItem(humanMeat);
  Weapon *speer = new Weapon(
      "speer", "An old speer from fallen knight. Has burn marks", 10);
  field->addItem(speer);

  /*
   * The third area on the map
   *
   */
  Room *rockyArea =
      new Room("Rocky Area",
               "You come to a rocky plateau. The wind carries the scent of"
               " death as its cold blow surrounds you. It is the plateau of "
               "the DarkKnight."
               " The fearsome brute who haunts the trails of the land."
               "\n\n The trail in front goes South and West");
  Enemy *darkKnight = new Enemy("DarkKnight", 50, R"(This guy is a jerk)");
  rockyArea->addCreature(darkKnight);
  Weapon *darkSword =
      new Weapon("darkSword", "A cursed sword that consumes souls", 10);
  darkKnight->addItem(darkSword);
  Food *mutton = new Food("mutton", "a large tasty chop of mutton", 50);
  darkKnight->addItem(mutton);

  Room *forest =
      new Room("forest",
               "The path leads you into a think forest. The trees block your "
               "vision of the plateau to the north and the cliffs to the west. "
               "The sounds of animals is drowned out by the chanting of an "
               "ancient language. Strange figures hang from the trees, strange "
               "herbs seem to be planted here. What people have been living "
               "here and what type of magic do they have?"
               "\n\n The trail goes north and west");
  Enemy *witch = new Enemy(
      "Witch", 50,
      "An ugly woman with a haunting gaze. Her tattered cloths reek "
      "of the blood of the children she's eaten. Around her neck hangs a vial"
      "of something magical. What could it be?");
  forest->addCreature(witch);
  Food *potion =
      new Food("MagicPotion",
               "A drink that radiates energy and brings immortality", 1000000);
  witch->addItem(potion);

  /*
   * The fifth area on the map
   * below field
   */
  Room *dragonLair =
      new Room("Dragon's lair",
               " You come to a rocky cliff side. In front of the cliffs "
               " At the bottom of the cliff is a mound of rock and human "
               "skulls, capped with gold coins and fine treasure."
               " It is the nest of the great red dragon!"
               "\n\n The trail goes east, south and west");
  Enemy *redDragon =
      new Enemy("redDragon", 200,
                "The great red dragon is a beast that brings terror to the "
                "hearts of the bravest heroes. From its nostrils smoke coils "
                "into the air.");
  Weapon *flameBreath = new Weapon(
      "flameBreath",
      "The unholy power to emit fire and cast it upon your enemies", 100);
  redDragon->addItem(flameBreath);
  Food *dragonMeat =
      new Food("dragonMeat", "Tough meat from the flesh of a dragon", 300);
  redDragon->addItem(dragonMeat);
  dragonLair->addCreature(redDragon);

  Room *plains = new Room(
      "The empty plains",
      "You come to the great salt plains that mark the border of King "
      "Erebus' realm. The scorching sun and salty soil prevent anything "
      "from growing here. You don't want to go any farther than this, for "
      "death awaits anyone tries to cross this barren land"
      "\n\nThe trail goes east");

  // basically creating a linked list of rooms
  home->setEast(field);
  field->setEast(rockyArea);
  forest->setNorth(rockyArea);
  dragonLair->setEast(forest);
  dragonLair->setWest(plains);

  _rooms.push_back(home);
  _rooms.push_back(field);
  _rooms.push_back(rockyArea);
  _rooms.push_back(forest);
  _rooms.push_back(dragonLair);
  _rooms.push_back(plains);

  return 0;
}

void Game::look(Player *player) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Our hero: %s",
            player->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Current Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Health: %d", player->getHealth());

  // This is a temp thing until I make text display line by line.
  _currentRow++;

  mvwprintw(_display_win, _currentRow++, 1, "%s",
            player->listInventory().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::look(const std::string &dir) {
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
    mvwprintw(_display_win, _currentRow++, 1,
              "You learn nothing from looking at %s", item->getName().c_str());
  } else {
    mvwprintw(_display_win, _currentRow++, 1, "%s",
              item->getDescription().c_str());
  }
  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::customResponse(const std::string &str) {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "%s", str.c_str());
  _currentRow += 4;
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1, "Location: %s",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Description:");
  mvwprintw(_display_win, _currentRow++, 1, "%s",
            _currentRoom->getDescription().c_str());

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  if (!_player->isAlive()) {
    noecho();
    mvwprintw(_input_win, 1, 1, "Cannot move... ");
    wrefresh(_input_win);
    sleep(4);
    deadScreen();
    return;
  }
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);
}

void Game::go(const std::string &dir) {
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
int Game::loadRoom(Room *room, char c, const Item *item) {
  std::string actionString;

  if (c == 'p') {
    actionString = "picks up";
  } else if (c == 'c') {
    actionString = "drops";
  } else {
    actionString = "does something with";
  }

  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "Player %s %s.",
            actionString.c_str(), item->getName().c_str());
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
int Game::deadScreen() {
  setDefaults();
  wclear(_display_win);
  wclear(_input_win);

  mvwprintw(_display_win, _currentRow++, 1, "%s %s is dead!!%s", u8"\U0001F480",
            _player->getName().c_str(), u8"\U0001F480");
  mvwprintw(_display_win, _currentRow++, 1, "");
  mvwprintw(_display_win, _currentRow++, 1,
            "Exit and reload to try again in your quest",
            _currentRoom->getName().c_str());
  mvwprintw(_display_win, _currentRow++, 1, "Type \"exit\" to end game");

  wrefresh(_display_win);

  box(_input_win, 0, 0);
  mvwprintw(_input_win, 1, 1, "Command: ");
  wrefresh(_input_win);

  return 0;
}
