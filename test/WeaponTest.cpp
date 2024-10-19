//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Weapon.h"

TEST(WeaponTest, DefaultConstructorTest) {
  Weapon *w = new Weapon("testWeapon", "A test weapon");

  EXPECT_EQ(w->getType(), "Weapon");
  EXPECT_EQ(w->getName(), "testWeapon");
  EXPECT_EQ(w->getDescription(), "A test weapon");
  EXPECT_GT(w->getDamage(), 1);

  delete w;
}

TEST(WeaponTest, RoomOwnerTest) {
  Weapon *w = new Weapon("testWeapon", "A test weapon");
  Room *r = new Room("testRoom");

  auto result = w->getOwner();

  EXPECT_FALSE(result.has_value());

  r->addItem(w);
  result = w->getOwner();
  EXPECT_TRUE(result.has_value());

  auto variant = result.value();
  if (std::holds_alternative<Room *>(variant)) {
    EXPECT_EQ(std::get<Room *>(variant), r);
  }

  delete r;
}

TEST(WeaponTest, CreatureOwnerTest) {
  Weapon *w = new Weapon("testWeapon", "A test weapon");
  Player *p = new Player("testUser", 100);

  auto result = w->getOwner();

  EXPECT_FALSE(result.has_value());

  p->addItem(w);
  result = w->getOwner();
  EXPECT_TRUE(result.has_value());
  // EXPECT_EQ(f->getOwner(), p);

  auto variant = result.value();
  if (std::holds_alternative<Creature *>(variant)) {
    EXPECT_EQ(std::get<Creature *>(variant), p);
  }

  delete p;
}
