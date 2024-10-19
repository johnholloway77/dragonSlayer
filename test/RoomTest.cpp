//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos".
//

#include <gtest/gtest.h>

#include "../include/Enemy.h"
#include "../include/Food.h"
#include "../include/Player.h"
#include "../include/Room.h"
#include "../include/Weapon.h"

TEST(RoomTest, ConstructorTest) {
  Room *r = new Room("testRoom", "A room for testing");

  EXPECT_EQ(r->getInventory().size(), 0);
  EXPECT_EQ(r->getName(), "testRoom");
  EXPECT_EQ(r->getDescription(), "A room for testing");
  EXPECT_TRUE(r->isAccessable());

  delete r;
}

TEST(RoomTest, AddTest) {
  Room *r = new Room("testRoom", "A room for testing");

  EXPECT_EQ(r->getInventory().size(), 0);
  EXPECT_EQ(r->getCreatures().size(), 0);

  Enemy *e = new Enemy("testEnemy", 100, "testEnemy");
  Weapon *w = new Weapon("testWeapon", "a weapon for testing", 5);

  r->addItem(w);
  r->addCreature(e);

  EXPECT_EQ(r->getInventory().size(), 1);
  EXPECT_EQ(r->getCreatures().size(), 1);
  EXPECT_EQ(e->getCurrentRoom(), r);

  delete r;
}

TEST(RoomTest, GetEnemyInventory) {
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

TEST(RoomTest, JoinRoomsTest) {
  Room *NW = new Room("testRoom", "A room for testing");
  Room *NE = new Room("testRoom", "A room for testing");
  Room *SE = new Room("testRoom", "A room for testing");
  Room *SW = new Room("testRoom", "A room for testing");

  NW->setEast(NE);
  NE->setSouth(SE);
  SE->setWest(SW);
  SW->setNorth(NW);

  EXPECT_EQ(NW->getEast(), NE);
  EXPECT_EQ(NE->getSouth(), SE);
  EXPECT_EQ(SE->getWest(), SW);
  EXPECT_EQ(SW->getNorth(), NW);

  // check for automatically setting its opposite room
  EXPECT_EQ(NE->getWest(), NW);
  EXPECT_EQ(NW->getSouth(), SW);
  EXPECT_EQ(SW->getEast(), SE);
  EXPECT_EQ(SE->getNorth(), NE);

  delete NE;
  delete NW;
  delete SW;
  delete SE;
}

TEST(RoomTest, HasCreatureTest) {
  Room *r = new Room("testRoom", "A room for testing");
  Enemy *e = new Enemy("testEnemy", 1, "testDesc");

  EXPECT_EQ(r->listCreatures(), "Nothing stands here");

  r->addCreature(e);
  EXPECT_EQ(r->getCreatures().size(), 1);
  EXPECT_EQ(r->listCreatures(), "- " + e->getName() + "\n");

  r->removeCreature(e);
  EXPECT_EQ(r->getCreatures().size(), 0);

  delete e;
  delete r;
}

TEST(RoomTest, HasItemTest) {
  Room *r = new Room("testRoom", "A room for testing");
  Weapon *w = new Weapon("testWeapon", "testWeapon");

  EXPECT_EQ(r->listItems(), "");

  r->addItem(w);
  EXPECT_EQ(r->getInventory().size(), 1);
  EXPECT_EQ(r->listItems(), "- " + w->getName() + "\n");

  r->removeItem(w);
  EXPECT_EQ(r->getInventory().size(), 0);

  delete w;
  delete r;
}
