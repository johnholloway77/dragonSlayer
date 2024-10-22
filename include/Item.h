//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <optional>
#include <string>
#include <variant>

#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_

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
  /**
   * @brief A constructor for the object that only accepts name. Will leave
   * _discription as an empty string
   * @param name The name of the object
   */
  explicit Item(const std::string& name) : _name(name) {}

  /**
   * @brief A constructor for Item objects taht takes a name and description
   * @param name A string representing the name of the object
   * @param desc A string that will be set as the object's description
   */
  Item(const std::string& name, const std::string& desc)
      : _name(name), _description(desc) {}

  /**
   * @brief An identifier returning what type of item the object is
   * @return A string identifying the object type
   */
  virtual std::string getType() const = 0;

  /**
   * @brief A function to get the name of the item
   * @return A reference to the object's name
   */
  const std::string& getName() const;

  /**
   * @brief A function to get the description of the item
   * @return A reference to the object's description
   */
  const std::string& getDescription() const;

  /**
   * @brief A function to get the owner of the object. Because an item can
   * either belong to a room or a creature, it must return an optional variant
   * that is a pointer to the Creature or the Room object containing the item.
   *
   * @return a std::optional which itself contains a std::variant of either a
   * Creature pointer or a Room pointer. The return value must be optional in
   * the event there isn't a current owner in which case a nullptr is returned.
   * If there is an owner, it can be of one of the two classes that can hold
   * items
   */
  std::optional<std::variant<Creature*, Room*>> getOwner();

  /**
   * @brief A function to set the current owner of the item. If the item's
   * curernt owner is not null pointer, the function will automatically remove
   * ownership for that item and assign it to the new owner.
   * @param newOwner A std::variant because the owner can be either a Room or a
   * Creature object
   */
  void setOwner(std::variant<Creature*, Room*> newOwner);

  /**
   * @brief Default destructor
   */
  virtual ~Item() {}
};

#endif  // INCLUDE_ITEM_H_
