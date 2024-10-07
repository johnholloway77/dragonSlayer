//
// Created by jholloway on 10/7/24.
//

#include <iostream>
#include <ncurses.h>
#include "../include/Game.h"
#include "../include/TitlePage.h"
#include "../include/Player.h"
#include "../include/Text.h"

Game::Game(){
    std::cout << "\033[?1049h";
    fflush(stdout);

    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
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
    endwin();
    printf("\033[?1049l");
    std::cout << "\nText game successfully exited" << std::endl;
}

void Game::setDefaults() {
    currentRow = 1;
    _inputText = "";
}

void Game::loadTitle() {
    curs_set(0);
    _title_win = newwin(_screen_height, _screen_width, 0, 0);
    mvwprintw(_title_win, 1, 1, title.c_str());
    wrefresh(_title_win);
    sleep(2);
    curs_set(1);
}

void Game::initPlayer() {
    setDefaults();
    mvwprintw(_display_win, currentRow++, 1, "Enter your name brave warrior!");
    wrefresh(_display_win);

    mvwprintw(_input_win, 1, 1, "Name: ");
    wrefresh(_input_win);

    echo();
    wgetnstr(_input_win, buffer, sizeof(buffer) - 1);
    _inputText = std::string(buffer);
    if(_inputText == "exit" || _inputText == "EXIT") return;

    _player = new Player(_inputText, 100, "Our lowly hero");
}

void Game::welcomeMessage() {
    setDefaults();
    wclear(_display_win);
    mvwprintw(_display_win, currentRow++, 1, "Welcome %s\n", _player->getName().c_str());
    mvwprintw(_display_win, currentRow++, 1, "%s\n", welcomeText.c_str());
    wrefresh(_display_win);

    mvwprintw(_input_win, 1, 1, "Press Enter to begin");
    wrefresh(_input_win);
    wgetnstr(_input_win, buffer, sizeof(buffer) - 1);


}
