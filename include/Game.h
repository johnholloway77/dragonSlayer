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

/**
 * @class Game Game.h "Game.h"
 * @brief The main loop for the game logic. Starts a ncurses session to build a
 * more interactive and stylish terminal based around the screen dimensions.
 * Creates the world map, populating it with enemies and items
 * Creates the player
 * Has a tool to parse the input of the user and call the appropriate function.
 * Really the main engine of the game
 */
class Game {
 private:
  bool _gameComplete;

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
  /**
   * @brief default constructor for Game. Starts an instance of the game engine
   */
  Game();

  /**
   * @brief default constrcutor for Game. Will delete all rooms in added to
   * _rooms to avoid memory leaks
   */
  ~Game();

  /**
   * @brief A function to set the default terminal output to UTF-8 to get the
   * sexy intro screen
   * @return int 0 if successful, 1 on error
   */
  int setDefaults();

  /**
   * @brief A function to load the titlescreen of the game
   * @return int 0 if successful, 1 on error
   */
  int loadTitle();

  /**
   * @brief A function to load a specific room. Will update the screen with the
   * name and description of the room. Title screen will appear for 4 seconds,
   * player will be unable to input during this time
   * @param room A pointer to a room object
   * @return int 0 if successful, 1 on error
   */
  int loadRoom(Room *room);

  /**
   * @brief A function to load a specific room, as well as a char to indicate if
   * a the player picks up an item from the room or drops an item in the room.
   * Screen will update notifying the player of the action performed upon the
   * item
   * @param room A pointer to the specific room in which the item is being
   * picked up or dropped
   * @param c 'p' to indicate if picking up item, 'd' to drop an item.
   * @param item A pointer to an item
   * @return int 0 if successful, 1 on error
   */
  int loadRoom(Room *room, char c, const Item *item);

  /**
   * @brief A function to search through the vector _rooms and load the one with
   * a maching name. Really just used to start the game
   * @param roomName a const string specifying a name of a room
   * @return int 0 if successful, 1 on error
   */
  int loadRoom(const std::string &roomName);

  /**
   * @brief A function to ask the player their name and then create a Player
   * object with the provided information
   * @return int 0 if successful, 1 on error
   */
  int initPlayer();

  /**
   * @brief A function to create the world map, the enemies and items inside the
   * world and add them to _rooms. In retrospect I should have created the
   * rooms, enemies and items using factory objects, but too late to refactor
   * now!
   * @return int 0 if successful, 1 on error
   */
  int initWorldMap();

  /**
   * @brief A function display a welcome message to the user. Player will need
   * to press enter to continue after reading
   * @return int 0 if successful, 1 on error
   */
  int welcomeMessage();

  /** A function to get the command entered by the user in to _inputWin.
   * Function will parse the user input and call the appropriate other functions
   * in response to user input. This function in is called in a loop by Game;
   * loop continues until get command returns -1
   *
   * User input is tokenized and added to a of vector<std::string>. For each
   token entered a series of if/else checks are performed to see if it is a
   valid, recognized word. Parsing continues until the vector is empty or four
   words have been parsed, whichever comes first. Extra words after the fourth
   are ignored.
   *
   * yeah I know, I probably could have found a more efficient way to build
   this, but I've never made a parser before. This stuff is new to me and so is
   C++ !!!
   *
   * @return int 0 if successful, 1 on error, -1 if player enters "exit" or
   * "quit"
   */
  int getCommand();

  /**
   * @brief A function than informs the user that the command they entered is
   * not valid. Will display the invalid command and then reload the room
   * details.
   * @param cmd const reference to the string entered by player
   * @param room The current room for the player
   * @return int 0 if successful, 1 on error
   */
  int invalidCommand(const std::string &cmd, Room *room);

  /**
   * @brief A function called when the player enters "inventory" or "look
   * player". Will list the players name, stats, heath, inventory and
   * description of inventory items
   * @param p
   */
  void look(Player *p);

  /**
   * @brief A function to look in a direction (eg west, north...) and get the
   * description of that area
   * @param dir a string specifying the cardinal direction the player wishes to
   * look
   */
  void look(const std::string &dir);

  /**
   * @brief A function to look at room in more detail. Will list the
   * description, but also the items and creatures that can be looked at for
   * more detail
   * @param room a pointer to a room object
   */
  void look(Room *room);

  /**
   * @brief A function to look at a creature and update the screen to show the
   * creature's description
   * @param creature A pointer to a creature object
   */
  void look(Creature *creature);

  /**
   * @brief A function to look at an item and update the screen with a
   * description of the item
   * @param item A pointer to an item object
   */
  void look(Item *item);

  /**
   * @brief A function to update the screen with a custom message to the user.
   * Will update the screen with the custom message and then display the basic
   * details of the current room
   * @param str a const reference that is the custom message you wish to share
   * to the user
   */
  void customResponse(const std::string &str);

  /**
   * @brief A function that tries to get the current room's pointer to the room
   * in the specified direction. If player mistypes and says "go foo" or some
   * other random word, player will be informed they cannot go in this direction
   * @param dir A string representing which direction the player wishes to trave
   */
  void go(const std::string &dir);

  /**
   * @brief A function that just passes the room pointer to loadRoom(Room
   * *room). Probably should delete this one but it's getting late
   * @param room A pointer to a Room object
   */
  void go(Room *room);

  /**
   * @brief When called it updates the screen to display the help page,
   * providing information on how to use the commands and play the game.
   */
  void helpScreen();

  /**
   * @brief A screen that appears when the player's health reaches 0, indicating
   * they've died. Player cannot move or enter any input on this screen except
   * exit
   * @return int 0 if successful, 1 on error
   */
  int deadScreen();

  /**
   * @brief A screen that appears when the player's current room equals an
   * exitRoom. Player cannot move or enter any input on this screen except exit
   * @return int 0 if successful, 1 on error
   */
  int winnerScreen();
};

#endif  // INCLUDE_GAME_H_
