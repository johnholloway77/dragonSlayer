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

protected:
    std::string _name;
    std::string _description;
public:

    Item(const std::string& name) : _name(name){};
    Item(const std::string& name, const std::string desc) : _name(name), _description(desc){};

    virtual std::string getType() const = 0;

    std::string getName() const;
    std::string getDescription() const;

    //virtual void pickup();

    //virtual void drop();

    virtual ~Item(){};
};

#endif //DRAGONSLAYER_ITEM_H
