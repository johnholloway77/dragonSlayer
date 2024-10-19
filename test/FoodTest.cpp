//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/Food.h"
#include "../include/Player.h"
#include "../include/Room.h"

TEST(FoodTest, DefaultConstructorTest) {
  Food *f = new Food("testFood", "FoodForTest", 100);

  EXPECT_EQ(f->getType(), "Food");
  EXPECT_EQ(f->getName(), "testFood");
  EXPECT_EQ(f->getDescription(), "FoodForTest");
  EXPECT_EQ(f->getHealth(), 100);
  auto result = f->getOwner();
  EXPECT_FALSE(result.has_value());

  delete f;
}

TEST(FoodTest, CreatureOwnerTest) {
  Food *f = new Food("testFood", "FoodForTest");
  Player *p = new Player("testUser", 100);

  auto result = f->getOwner();

  EXPECT_FALSE(result.has_value());

  p->addItem(f);
  result = f->getOwner();
  EXPECT_TRUE(result.has_value());
  // EXPECT_EQ(f->getOwner(), p);

  auto variant = result.value();
  if (std::holds_alternative<Creature *>(variant)) {
    EXPECT_EQ(std::get<Creature *>(variant), p);
  }

  delete p;
}

TEST(FoodTest, RoomOwnerTest) {
  Food *f = new Food("testFood", "FoodForTest", 100);
  Room *r = new Room("testRoom");

  auto result = f->getOwner();

  EXPECT_FALSE(result.has_value());

  r->addItem(f);
  result = f->getOwner();
  EXPECT_TRUE(result.has_value());

  auto variant = result.value();
  if (std::holds_alternative<Room *>(variant)) {
    EXPECT_EQ(std::get<Room *>(variant), r);
  }

  delete r;
}
