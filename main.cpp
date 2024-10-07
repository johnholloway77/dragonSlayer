#include <iostream>
#include "include/Player.h"
#include "include/Sword.h"
#include "include/Room.h"

int main() {
    std::cout << "Hello, what is your name" << std::endl;
    std::string name;

    std::cin >> name;

    Player *p1 = new Player(name, 100);
    Sword *s1 = new Sword("StormBringer");
    Sword *s2 = new Sword("DeathBringer", "A deadly sword made cursed with the soul of its enemies", 15);

    while(p1->isAlive()){

        std::cout << p1->getName() << std::endl;
        std::cout << p1->listInventory() << std::endl;

        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;

        p1->addToInventory(s1);
        p1->addToInventory(s2);
        std::cout << p1->listInventory() << std::endl;

        p1->hurt(100);
        std::cout << "health: " << p1->getHealth() << std::endl;
        std::cout << "is " << p1->getName() << " alive? " << (p1->isAlive() ? "Yes!" : "No") << std::endl;
    }

    std::cout << "You're dead " << p1->getName() << "!" << std::endl;

    Room *field = new Room("field", "A vast field");

    std::cout << field->getName() << " " << field->getDescription() << std::endl;
    std::cout << "N: " << field->lookNorth() << ". E " << field->lookEast() << ", S " << field->lookSouth() << ", W: " << field->lookWest() << std::endl;


    delete p1;
    delete s1;
    delete s2;
    delete field;;

    return 0;
}
