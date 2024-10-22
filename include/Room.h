//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#ifndef INCLUDE_ROOM_H_
#define INCLUDE_ROOM_H_

#include <string>
#include <vector>

#include "Item.h"

class Item;

/**
 * @brief Room's are objects that can contain items, creatures, description data
 * and pointers to other rooms. They are loaded when a player goes in a
 * direction and the room in set to accessible
 */
class Room {
 protected:
  Room *_north = nullptr;
  Room *_east = nullptr;
  Room *_south = nullptr;
  Room *_west = nullptr;

  bool _accessable = true;

  std::string _name;
  std::string _description;
  std::vector<Item *> _inventory;
  std::vector<Creature *> _creatures;

 public:
  /**
   * @brief A constructor for room objects. Only sets the name. useful only
   * really for testing
   * @param name a const reference to a string for name
   */
  explicit Room(const std::string &name) : _name(name) {}

  /**
   * @brief A constructor to create a room object. Use it to set the name and
   * description of the room, but will use the default value of "true" for
   * accessable
   * @param name a const reference to a string for name
   * @param desc a const reference to a string for description
   */
  Room(const std::string &name, const std::string &desc)
      : _name(name), _description(desc) {}

  /**
   * @brief A constructor for creating a room. Unlike other constructor, you can
   * set the accessible bool at instantiation
   * @param name a const reference to a string for name
   * @param accessable A bool indicating whether or not the room is accessible
   * @param desc a const reference to a string for description
   */
  Room(const std::string &name, bool accessable, const std::string &desc)
      : _name(name), _accessable(accessable), _description(desc) {}

  /**
   * @brief to get the name of the room
   * @return a const reference to _name
   */
  const std::string &getName();

  /**
   * @brief to get the description of the room
   * @return A const reference to _description
   */
  const std::string &getDescription();

  /**
   * @brief A function to create a string listing all of the items contained by
   * this room separated by newline characters and prefixed with -
   * @return a string for all items in room. Empty string if no items.
   */
  std::string listItems();

  /**
   * @brief A function to create a string listing all of the Creatures contained
   * by this room separated by newline characters and prefixed with -
   * @return a string for all items in room. Empty string if no Creatures.
   */
  std::string listCreatures();

  /**
   * @brief used to set the room to the north of the current room object. If the
   * south pointer in the argument room is nullptr, then the function will
   * automatically set the current room to south for the argument room. This is
   * to speed up map creation
   * @param north a pointer to the room that will be north of this one
   */
  void setNorth(Room *north);

  /**
   * @brief used to set the room to the east of the current room object. If the
   * west pointer in the argument room is nullptr, then the function will
   * automatically set the current room to west for the argument room. This is
   * to speed up map creation
   * @param east A pointer to the room to the east of this one
   */
  void setEast(Room *east);

  /**
   * @brief used to set the room to the south of the current room object. If the
   * north pointer in the argument room is nullptr, then the function will
   * automatically set the current room to north for the argument room. This is
   * to speed up map creation
   * @param south A pointer to the room object to be south of this one
   */
  void setSouth(Room *south);

  /**
   * @brief used to set the room to the west of the current room object. If the
   * east pointer in the argument room is nullptr, then the function will
   * automatically set the current room to east for the argument room. This is
   * to speed up map creation
   * @param west A pointer to the room object to be west of this one
   */
  void setWest(Room *west);

  /**
   * @brief get a pointer to the room north of this room
   * @return a pointer of type room if _north is set. If not, nullprt is
   * returned
   */
  Room *getNorth();

  /**
   * @brief get a pointer to the room east of this room
   * @return a pointer of type room if _east is set. If not, nullprt is returned
   */
  Room *getEast();

  /**
   * @brief get a pointer to the room south of this room
   * @return a pointer of type room if _west is set. If not, nullprt is returned
   */
  Room *getSouth();

  /**
   * @brief get a pointer to the room west of this room
   * @return a pointer of type room if _west is set. If not, nullprt is returned
   */
  Room *getWest();

  /**
   * @brief A function to add an item to this room. If the item already has an
   * owner, function will remove the current owner's collection and set the
   * owner to the room object
   * @param item
   */
  void addItem(Item *item);

  /**
   * @brief A function to remove the item from _inventory collection
   * @param item
   */
  void removeItem(Item *item);

  /**
   * @brief A function to return a const reference to the inventory of this
   * room. Useful for when game needs to check if the inventory contains an item
   * matching a specific name
   * @return a vector of pointers of Item objects
   */
  const std::vector<Item *> &getInventory();

  /**
   * @brief A function to add creatures to the room. As the creatures do not
   * move around the map, there is no need to check if a creature already has an
   * owner room.
   * @param creature A pointer to a Creature object
   */
  void addCreature(Creature *creature);

  /**
   * @brief A function
   * @param creature
   */
  void removeCreature(Creature *creature);

  /**
   * @brief A function to return a const reference to the creatures of this
   * room. Useful for when game needs to check if the room contains a creature
   * matching a specific name
   * @return a vector of pointers of Item objects
   */
  const std::vector<Creature *> &getCreatures();

  /**
   * @brief A function to check if the room is accessible. Used by
   * Game::LoadRoom to see if the player can access the room before loading it
   * @return a bool indicating the value of _accessable
   */
  virtual bool isAccessable();

  /**
   * @brief A destructor for the room. Will delete all Items and Creature
   * objects inside of the room to avoid memory leaks when called.
   */
  ~Room();
};

#endif  // INCLUDE_ROOM_H_
