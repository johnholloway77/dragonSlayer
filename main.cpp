#include <iostream>
#include "include/Player.h"
#include "include/Sword.h"
#include "include/Room.h"
#include "include/Food.h"

int main() {
    std::cout << "Hello, what is your name" << std::endl;
    std::string name;

    std::cin >> name;

    Player *p1 = new Player(name, 100, "Our lowly hero");
    Sword *s1 = new Sword("StormBringer");
    Sword *s2 = new Sword("DeathBringer", "A deadly sword made cursed with the soul of its enemies", 15);

    Food *muffin = new Food("muffin");


    std::cout << p1->getName() << std::endl;
    std::cout << p1->getDescription() << std::endl;
    std::cout << p1->listInventory() << std::endl;

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

    return 0;
}
