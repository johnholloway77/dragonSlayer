#include <iostream>
#include "include/Player.h"

int main() {
    std::cout << "Hello, what is your name" << std::endl;
    std::string name;

    std::cin >> name;

    Player p1 = Player(name);

    std::cout << p1.getName() << std::endl;
    std::cout << p1.listInventory() << std::endl;



    return 0;
}
