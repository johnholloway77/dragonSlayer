//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//
#include <gtest/gtest.h>

#include "../include/Enemy.h"
#include "../include/Food.h"
#include "../include/Player.h"
#include "../include/Room.h"

TEST(EnemyTest, ConstructorTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");

  EXPECT_EQ(e->getName(), "testEnemy");
  EXPECT_EQ(e->getHealth(), 100);
  EXPECT_EQ(e->getDescription(), "testDesc");
  EXPECT_EQ(e->getType(), "Enemy");
  EXPECT_EQ(e->getCurrentRoom(), nullptr);

  delete e;
}

TEST(EnemyTest, AddFoodTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Food *f = new Food("testFood");

  EXPECT_EQ(e->getInventory().size(), 0);
  e->addItem(f);

  EXPECT_EQ(e->getInventory().size(), 1);

  delete e;
}

TEST(EnemyTest, AddWeaponTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Weapon *w = new Weapon("testWeapon");

  EXPECT_EQ(e->getInventory().size(), 0);
  e->addItem(w);

  EXPECT_EQ(e->getInventory().size(), 1);

  delete e;
}

TEST(EnemyTest, HurtTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(e->getHealth(), 100);
  p->attack(e);
  EXPECT_LE(e->getHealth(), 100);

  delete e;
  delete p;
}

TEST(EnemyTest, AttackHandsTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(e->getHealth(), 100);
  p->attack(e);
  EXPECT_TRUE(e->getHealth() >= 90 && e->getHealth() < 100);

  delete e;
  delete p;
}

TEST(EnemyTest, AttackWeaponTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);
  Weapon *w = new Weapon("testWeapon", "a weapon for testing", 5);

  EXPECT_EQ(e->getHealth(), 100);
  p->addItem(w);
  p->attack(e, w);
  EXPECT_TRUE(e->getHealth() >= 50 && e->getHealth() <= 95);

  delete e;
  delete p;
}

TEST(EnemyTest, AttackFoodTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood", 50);

  EXPECT_EQ(e->getHealth(), 100);
  p->addItem(f);
  p->attack(e, f);
  EXPECT_EQ(e->getHealth(), 100);

  delete e;
  delete p;
}

TEST(EnemyTest, RetaliateTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(e->getHealth(), 100);
  p->attack(e);
  EXPECT_LE(e->getHealth(), 100);
  EXPECT_LE(p->getHealth(), 100);

  delete e;
  delete p;
}

TEST(EnemyTest, DeathTest) {
  Enemy *e = new Enemy("testEnemy", 1, "testDesc");
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(e->isAlive(), true);

  p->attack(e);

  EXPECT_LE(e->getHealth(), 0);
  EXPECT_EQ(e->isAlive(), false);

  EXPECT_EQ(p->attack(e),
            "You cannot hurt " + e->getName() + " as it's already dead");

  delete p;
  delete e;
}

TEST(EnemyTest, DropInventory) {
  Enemy *e = new Enemy("testEnemy", 1, "testDesc");
  Player *p = new Player("testUser", 100);
  Food *f = new Food("testFood");
  Weapon *w = new Weapon("testWeapon");
  Room *room = new Room("testRoom", "A room for testing");

  e->addItem(f);
  e->addItem(w);
  room->addCreature(e);
  EXPECT_EQ(room->getInventory().size(), 0);
  EXPECT_EQ(e->getInventory().size(), 2);
  EXPECT_EQ(e->isAlive(), true);

  p->attack(e);

  EXPECT_LE(e->getHealth(), 0);
  EXPECT_EQ(e->isAlive(), false);

  EXPECT_EQ(e->getInventory().size(), 0);
  EXPECT_EQ(room->getInventory().size(), 2);
  delete p;
  delete room;
}

TEST(EnemyTest, AttackFoodResponseTest) {
  Enemy *e = new Enemy("testEnemy", 100, "testDesc");
  Player *p = new Player("testUser", 100);
  Weapon *w = new Weapon("testWeapon");
  Food *f = new Food("testFood");

  EXPECT_EQ(e->getHealth(), 100);
  e->addItem(w);
  e->attack(p, w);
  EXPECT_LT(p->getHealth(), 100);

  delete e;
  delete p;
}
