//
// Created by jholloway on 10/7/24.
//

#include <iostream>
#include <ncurses.h>
#include "../include/Game.h"
#include "../include/Player.h"
#include "../include/Text.h"
#include "../include/Room.h"
#include "../include/Food.h"
#include "../include/Weapon.h"
#include "../include/Enemy.h"

Game::Game(){
    std::cout << "\033[?1049h";
    fflush(stdout);

    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    //noecho();
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, _screen_height, _screen_width);
    _input_height = _screen_height / 5;
    _display_height = _screen_height - _input_height;

    loadTitle();

    _display_win = newwin(_display_height, _screen_width, 0, 0);
    _input_win = newwin(_input_height, _screen_width, _display_height, 0);
    delwin(_title_win);

    scrollok(_display_win, true);
    //box(display_win, 0, 0);
    box(_input_win, 0, 0);
    wrefresh(_display_win);
    wrefresh(_input_win);

    //Do I even need these anymore?
    _input_win_width = _screen_width - 2;
    _display_win_width = _screen_width - 2;


}

Game::~Game() {

    delete _player;

    for(Room *room : _rooms){
        delete room;
    }

    endwin();
    printf("\033[?1049l");
    std::cout << "\nText game successfully exited" << std::endl;
}

int Game::setDefaults() {
    _currentRow = 1;
    _inputText = "";
    //noecho();

    return 0;
}

int Game::loadTitle() {
    curs_set(0);
    _title_win = newwin(_screen_height, _screen_width, 0, 0);
    mvwprintw(_title_win, 1, 1, title.c_str());
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

    if(_inputText == "exit" || _inputText == "EXIT") {
        return -1;
    };

    _player = new Player(_inputText, 100, "Our lowly hero");

    return 0;
}

int Game::welcomeMessage() {
    setDefaults();
    wclear(_display_win);
    mvwprintw(_display_win, _currentRow++, 1, "Welcome %s\n", _player->getName().c_str());
    mvwprintw(_display_win, _currentRow++, 1, "%s\n", welcomeText.c_str());
    wrefresh(_display_win);

    mvwprintw(_input_win, 1, 1, "Press Enter to begin");
    wrefresh(_input_win);
    wgetnstr(_input_win, buffer, sizeof(buffer) - 1);

    return 0;
}


int Game::loadRoom(std::string roomName) {
    for(Room *room : _rooms){
        if(room && room->getName() == roomName){
            loadRoom(room);
            return 0;
        }
    }

    return -1;
}

int Game::lookRoom(Room *room) {
    setDefaults();
    wclear(_display_win);
    wclear(_input_win);

    mvwprintw(_display_win, _currentRow++, 1, "Location: %s", room->getName().c_str());

    mvwprintw(_display_win, _currentRow++, 1, "Items you see:");
    mvwprintw(_display_win, _currentRow++, 1, "%s", room->listItems().c_str());
    wrefresh(_display_win);


    box(_input_win, 0, 0);
    mvwprintw(_input_win, 1, 1, "Command: ");
    wrefresh(_input_win);

    return 0;
}

int Game::lookDirection(std::string dir) {
    Room* room;

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
    if(!room) {
        mvwprintw(_display_win, _currentRow++, 1, "There is nothing in that direction");
    }else{
        mvwprintw(_display_win, _currentRow++, 1, "You see %s", room->getName().c_str());
    }
        wrefresh(_display_win);

        box(_input_win, 0, 0);
        mvwprintw(_input_win, 1, 1, "Command: ");
        wrefresh(_input_win);

        return 0;



}

int Game::loadRoom(Room *room){

    _currentRoom = room;

    setDefaults();
    wclear(_display_win);
    wclear(_input_win);

    mvwprintw(_display_win, _currentRow++, 1, "Location: %s", room->getName().c_str());
    mvwprintw(_display_win, _currentRow++, 1, "Description:");
    mvwprintw(_display_win, _currentRow++, 1, "%s", room->getDescription().c_str());
    //mvwprintw(_display_win, _currentRow++, 1, "Items you see:");
    //mvwprintw(_display_win, _currentRow++, 1, "%s", room->listItems().c_str());
    wrefresh(_display_win);


    box(_input_win, 0, 0);
    mvwprintw(_input_win, 1, 1, "Command: ");
    wrefresh(_input_win);

    return 0;
}

int Game::getCommand() {
    echo();
    wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
    _inputText = std::string(buffer);

    if(_inputText == "exit" || _inputText == "EXIT") {
        return -1;
    };

    if(_inputText == "look" || _inputText == "LOOK"){
        lookRoom(_currentRoom);
        return 0;
    }

    if(_inputText == "look east" || _inputText == "LOOK EAST"){
        lookDirection("east");
        return 0;
    }

    //loadRoom(_currentRoom);
    invalidCommand(_inputText, _currentRoom);
    return 0;
}


int Game::invalidCommand(std::string cmd, Room *room){
    setDefaults();
    wclear(_display_win);
    wclear(_input_win);

    mvwprintw(_display_win, _currentRow++, 1, "Sorry,");
    mvwprintw(_display_win, _currentRow++, 1, "I don't understand: %s", cmd.c_str());
    mvwprintw(_display_win, _currentRow++, 1, "");
    mvwprintw(_display_win, _currentRow++, 1, "Location: %s", room->getName().c_str());
    mvwprintw(_display_win, _currentRow++, 1, "Description:");
    mvwprintw(_display_win, _currentRow++, 1, "%s", room->getDescription().c_str());

    wrefresh(_display_win);


    box(_input_win, 0, 0);
    mvwprintw(_input_win, 1, 1, "Command: ");
    wrefresh(_input_win);
    return 0;
}

int Game::initWorldMap() {


    Room* home = new Room("Home",
                          "You are outside of your thatched roof cottage. The top of the roof"
                          " is smoking from a recent dragon attack. Ironically you were preparing food at the"
                          " time, so you won't have to bake it yourself."
                          " As a peasant your cannot afford to build a new roof"
                          "\n\nCould be worse...at least you don't have student loans");
    Food *muffin = new Food("muffin");
    home->addItem(muffin);


    Room *field = new Room("Field",
                           R"(You are in a field where you see the charred remains of fallen
                                    knights from the dragon attack. Some are still smoking with a odd smell.\n
                                    You find yourself getting hungry at the smell, but remind yourself that you are
                                    better than that. Plus you think it will give you an upset tummy.)"
                                    );
    Food *humanMeat = new Food("humanMeat", "Forbidden barbequed meat", 15);
    field->addItem(humanMeat);
    Weapon *speer = new Weapon("speer",
                               "An old speer from fallen knight. Has burn marks",
                               10);
    field->addItem(speer);

    Room *rockyArea = new Room("Rocky Area",
                               R"(You come to a rocky plateau. The wind carries the scent of
                                            death as its cold blow surrounds you. It is the plateau of the Dark Knight.
                                            The fearsome brute who haunts the trails of the land.)"
                                );
    Enemy *darkKnight = new Enemy("Dark Knight",
                                        50,
                                        R"(This guy is a jerk)");
    rockyArea->addCreature(darkKnight);

    //basically creating a linked list of rooms
    home->setEast(field);
    field->setEast(rockyArea);

    _rooms.push_back(home);
    _rooms.push_back(field);
    _rooms.push_back(rockyArea);

    return 0;
}