#include <ncurses.h>
#include <unistd.h>

#include <cctype>
#include <iostream>

#include "include/Food.h"
#include "include/Game.h"
#include "include/Player.h"
#include "include/Room.h"
#include "include/Weapon.h"

void init() {}

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
  // game.start();

  while (game.getCommand() != -1) {
  }

  //    while(input != "exit" || input != "EXIT"){
  //
  //        char buffer[256];
  //
  //        int currentRow = 1;
  //
  //
  //        mvwprintw(display_win, currentRow++, 1, "Enter your name brave
  //        warrior!"); wrefresh(display_win);
  //
  //        mvwprintw(input_win, 1, 1, "Name: ");
  //        wrefresh(input_win);
  //
  //        echo();
  //        wgetnstr(input_win, buffer, sizeof(buffer) - 1);
  //        input = std::string(buffer);
  //        if(input == "exit" || input == "EXIT") break;
  //        name = input;
  //
  //        Player *p1 = new Player(name, 100, "Our lowly hero");
  //        Weapon *s1 = new Weapon("StormBringer");
  //        Weapon *s2 = new Weapon("DeathBringer", "A deadly sword made cursed
  //        with the soul of its enemies", 15);
  //
  //        Food *muffin = new Food("muffin");
  //
  //        mvwprintw(display_win, (--currentRow)++, 1, "welcome %s\n",
  //        p1->getName().c_str()); mvwprintw(display_win, currentRow++, 1,
  //        "%s", p1->getDescription().c_str()); mvwprintw(display_win,
  //        currentRow++, 1, "%s", p1->listInventory().c_str());
  //        wrefresh(display_win);
  //        sleep(5);
  //
  //        std::cout << "health: " << p1->getHealth() << std::endl;
  //        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive()
  //        ? "Yes!" : "No") << std::endl;
  //
  //        p1->addItem(s1);
  //        p1->addItem(s2);
  //        p1->addItem(muffin);
  //        std::cout << p1->listInventory() << std::endl;
  //
  //        //while(p1->isAlive()){
  //
  //        std::cout << p1->attack() << std::endl;
  //
  //        std::cout << p1->attack(p1) << std::endl;
  //        std::cout << "health: " << p1->getHealth() << std::endl;
  //        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive()
  //        ? "Yes!" : "No") << std::endl;
  //
  //        std::cout << p1->attack(p1, muffin) << std::endl;
  //        std::cout << "health: " << p1->getHealth() << std::endl;
  //        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive()
  //        ? "Yes!" : "No") << std::endl;
  //
  //        std::cout << p1->attack(p1, s2) << std::endl;
  //        std::cout << "health: " << p1->getHealth() << std::endl;
  //        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive()
  //        ? "Yes!" : "No") << std::endl;
  //
  //        std::cout << p1->useItem(muffin) << std::endl;
  //
  //        std::cout << p1->listInventory() << std::endl;
  //        //}
  //
  //
  //
  //        //std::cout << "You're dead " << p1->getName() << "!" << std::endl;
  //
  //        Room *field = new Room("field", "A vast field");
  //
  //        std::cout << field->getName() << " " << field->getDescription() <<
  //        std::endl; std::cout << "N: " << field->lookNorth() << ". E " <<
  //        field->lookEast() << ", S " << field->lookSouth() << ", W: " <<
  //        field->lookWest() << std::endl;
  //
  //        std::cout << "The following items are in " << field->getName() <<
  //        "\n" << field->listItems() << std::endl; field->addItem(s1);
  //        field->addItem(s2);
  //        std::cout << "The following items are in " << field->getName() <<
  //        "\n" << field->listItems() << std::endl;
  //
  //
  //        delete p1;
  //        delete s1;
  //        delete s2;
  //        delete field;
  //    }

  return 0;
}
