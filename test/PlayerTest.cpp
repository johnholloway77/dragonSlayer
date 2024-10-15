//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/Food.h"
#include "../include/Player.h"
#include "../include/Weapon.h"

TEST(PlayerTest, defaultConstructorTest) {
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(p->getName(), "testUser");
  EXPECT_EQ(p->getHealth(), 100);

  delete p;
}

TEST(PlayerTest, addFoodItemTest) {
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood");

  EXPECT_EQ(p->getInventory().size(), 0);

  p->addItem(f);

  EXPECT_EQ(p->getInventory().size(), 1);

  delete p;
}

TEST(PlayerTest, addWeaponItemTest) {
  Player *p = new Player("testUser", 100);
  Weapon *w = new Weapon("testWeapon");

  EXPECT_EQ(p->getInventory().size(), 0);

  p->addItem(w);

  EXPECT_EQ(p->getInventory().size(), 1);

  delete p;
}

TEST(PlayerTest, addFoodHealthTest) {
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood", 50);

  EXPECT_EQ(p->getHealth(), 100);
  EXPECT_EQ(p->getInventory().size(), 0);

  p->addItem(f);
  EXPECT_EQ(p->getInventory().size(), 1);

  p->useItem(f);
  EXPECT_EQ(p->getHealth(), 150);
  EXPECT_EQ(p->getInventory().size(), 0);

  delete p;
}

TEST(PlayerTest, addFoodPoisonTest) {
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood", -150);

  EXPECT_EQ(p->getHealth(), 100);
  EXPECT_EQ(p->getInventory().size(), 0);
  EXPECT_EQ(p->isAlive(), true);

  p->addItem(f);
  EXPECT_EQ(p->getInventory().size(), 1);

  p->useItem(f);
  EXPECT_EQ(p->getHealth(), -50);
  EXPECT_EQ(p->getInventory().size(), 0);
  EXPECT_EQ(p->isAlive(), false);

  delete p;
}
