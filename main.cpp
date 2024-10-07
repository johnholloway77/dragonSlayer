#include <iostream>
#include "include/Player.h"

int main() {
    std::cout << "Hello, what is your name" << std::endl;
    std::string name;

    std::cin >> name;

    Player p1 = Player(name, 100);

    std::cout << p1.getName() << std::endl;
    std::cout << p1.listInventory() << std::endl;

    std::cout << "health: " << p1.getHealth() << std::endl;
    std::cout << "is " << p1.getName() << " alive? " << (p1.isAlive() ? "Yes!" : "No");

    p1.hurt(100);
    std::cout << "health: " << p1.getHealth() << std::endl;
    std::cout << "is " << p1.getName() << " alive? " << (p1.isAlive() ? "Yes!" : "No");

    return 0;
}
