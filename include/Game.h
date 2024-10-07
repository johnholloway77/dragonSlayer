//
// Created by jholloway on 10/7/24.
//

#ifndef DRAGONSLAYER_GAME_H
#define DRAGONSLAYER_GAME_H

#include <string>
#include <cctype>
#include <ncurses.h>
#include <unistd.h>

#include "Player.h"

class Game{

private:
    int _screen_height;
    int _screen_width;
    int _input_height;
    int _display_height;

    int _input_win_width;
    int _display_win_width;

    WINDOW* _title_win;
    WINDOW* _display_win;
    WINDOW* _input_win;

    char buffer[256];
    std::string _inputText;

    int currentRow = 1;

    Player* _player = nullptr;

public:
    Game();
    ~Game();

    void setDefaults();
    void loadTitle();
    void initPlayer();
    void welcomeMessage();

};

#endif //DRAGONSLAYER_GAME_H
