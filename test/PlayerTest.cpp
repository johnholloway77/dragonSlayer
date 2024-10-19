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
  EXPECT_EQ(p->getType(), "Player");

  delete p;
}

TEST(PlayerTest, alternateConstructorTest) {
  Player *p = new Player("testUser", 100, "testUser");

  EXPECT_EQ(p->getName(), "testUser");
  EXPECT_EQ(p->getHealth(), 100);
  EXPECT_EQ(p->getType(), "Player");
  EXPECT_EQ(p->getDescription(), "testUser");

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

TEST(PlayerTest, attackAtNothingtest) {
  Player *p = new Player("testUser", 100);
  EXPECT_EQ(p->attack(), "You attack at nothing and look like a fool!");
  delete p;
}

TEST(PlayerTest, InventoryTest) {
  Player *p = new Player("testUser", 100);
  EXPECT_EQ(p->listInventory(), p->getName() + " has the following items\n");

  delete p;
}

TEST(PlayerTest, FoodInventoryTest) {
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood", -150);

  p->addItem(f);
  EXPECT_EQ(p->listInventory(), p->getName() +
                                    " has the following items\n"
                                    "- " +
                                    f->getName() + " Type: " + f->getType() +
                                    "\n" +
                                    "\tNothing is known about this item\n");

  delete p;
}

TEST(PlayerTest, WeaponInventoryTest) {
  Player *p = new Player("testUser", 100);
  Weapon *w = new Weapon("testWeapon", "testDisc");

  p->addItem(w);
  EXPECT_EQ(p->listInventory(), p->getName() +
                                    " has the following items\n"
                                    "- " +
                                    w->getName() + " Type: " + w->getType() +
                                    "\n" + "\t" + w->getDescription() + "\n");

  delete p;
}
