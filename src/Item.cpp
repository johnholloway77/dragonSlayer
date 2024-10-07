//
// Created by jholloway on 10/6/24.
//

#include <iostream>
#include "../include/Item.h"

std::string Item::getName() const{
    return _name;
};

std::string Item::getDescription() const{
    return _description;
}