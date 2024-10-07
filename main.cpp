#include <iostream>
#include <cctype>
#include <ncurses.h>
#include <unistd.h>
#include "include/Player.h"
#include "include/Sword.h"
#include "include/Room.h"
#include "include/Food.h"

#include "include/TitlePage.h"

int main() {

    std::cout << "\033[?1049h";
    fflush(stdout);

    setlocale(LC_ALL, "");

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int screen_height;
    int screen_width;
    getmaxyx(stdscr, screen_height, screen_width);

    int input_height = screen_height / 5;
    int display_height = screen_height - input_height;

    WINDOW* title_win = newwin(screen_height, screen_width, 0, 0);
    //box(title_win, 0, 0);

    mvwprintw(title_win, 1, 1, title.c_str());
    wrefresh(title_win);
    sleep(2);


    WINDOW* display_win = newwin(display_height, screen_width, 0, 0);
    WINDOW* input_win = newwin(input_height, screen_width, display_height, 0);
    delwin(title_win);

    scrollok(display_win, true);
    //box(display_win, 0, 0);
    box(input_win, 0, 0);

    wrefresh(display_win);
    wrefresh(input_win);
    int input_win_width = screen_width - 2; // Window width excluding borders
    int display_win_width = screen_width - 2; // Window width excluding border

    std::string input;
    std::string name;
    bool input_started = false;

    while(name == ""){

        char buffer[256];

        int currentRow = 1;


        mvwprintw(display_win, currentRow++, 1, "Enter your name brave warrior!");
        wrefresh(display_win);

        mvwprintw(input_win, 1, 1, "Name: ");
        wrefresh(input_win);

        echo();
        wgetnstr(input_win, buffer, sizeof(buffer) - 1);
        input = std::string(buffer);
        if(input == "exit" || input == "EXIT") break;
        name = input;

        Player *p1 = new Player(name, 100, "Our lowly hero");
        Sword *s1 = new Sword("StormBringer");
        Sword *s2 = new Sword("DeathBringer", "A deadly sword made cursed with the soul of its enemies", 15);

        Food *muffin = new Food("muffin");

        mvwprintw(display_win, (--currentRow)++, 1, "welcome %s\n", p1->getName().c_str());
        mvwprintw(display_win, currentRow++, 1, "%s", p1->getDescription().c_str());
        mvwprintw(display_win, currentRow++, 1, "%s", p1->listInventory().c_str());
        wrefresh(display_win);
        sleep(5);

        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;

        p1->addItem(s1);
        p1->addItem(s2);
        p1->addItem(muffin);
        std::cout << p1->listInventory() << std::endl;

        //while(p1->isAlive()){

        std::cout << p1->attack() << std::endl;

        std::cout << p1->attack(p1) << std::endl;
        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;

        std::cout << p1->attack(p1, muffin) << std::endl;
        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;

        std::cout << p1->attack(p1, s2) << std::endl;
        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;

        std::cout << p1->useItem(muffin) << std::endl;

        std::cout << p1->listInventory() << std::endl;
        //}



        //std::cout << "You're dead " << p1->getName() << "!" << std::endl;

        Room *field = new Room("field", "A vast field");

        std::cout << field->getName() << " " << field->getDescription() << std::endl;
        std::cout << "N: " << field->lookNorth() << ". E " << field->lookEast() << ", S " << field->lookSouth() << ", W: " << field->lookWest() << std::endl;

        std::cout << "The following items are in " << field->getName() << "\n" << field->listItems() << std::endl;
        field->addItem(s1);
        field->addItem(s2);
        std::cout << "The following items are in " << field->getName() << "\n" << field->listItems() << std::endl;


        delete p1;
        delete s1;
        delete s2;
        delete field;
    }

    endwin();
    printf("\033[?1049l");
    //std::cout << "\nText game successfully exited" << std::endl;

    return 0;

    return 0;
}
