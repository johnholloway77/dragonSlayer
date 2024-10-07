//
// Created by jholloway on 10/6/24.
//

#include <string>

#ifndef DRAGONSLAYER_ITEM_H
#define DRAGONSLAYER_ITEM_H
/**
 *  @class Item Item.h "Item.h"
 *  @brief abstract class for items
 */
class Item{

private:
    std::string name;

public:

    virtual std::string getName() const{
        return name;
    }

    virtual void pickup() const = 0;

    virtual void drop() const = 0;

    virtual ~Item(){};
};

#endif //DRAGONSLAYER_ITEM_H
