//
// Created by jholloway on 10/6/24.
//

#include <optional>
#include <string>
#include <variant>

#ifndef DRAGONSLAYER_ITEM_H
#define DRAGONSLAYER_ITEM_H

class Creature;
class Room;

/**
 *  @class Item Item.h "Item.h"
 *  @brief abstract class for items
 */
class Item {
 protected:
  std::string _name;
  std::string _description;
  std::optional<std::variant<Creature*, Room*>> _owner = std::nullopt;

 public:
  Item(const std::string& name) : _name(name){};
  Item(const std::string& name, const std::string& desc)
      : _name(name), _description(desc){};

  virtual std::string getType() const = 0;

  std::string getName() const;
  std::string getDescription() const;
  std::optional<std::variant<Creature*, Room*>> getOwner();
  void setOwner(std::variant<Creature*, Room*> newOwner);

  virtual ~Item(){};
};

#endif  // DRAGONSLAYER_ITEM_H
