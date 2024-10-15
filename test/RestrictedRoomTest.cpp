//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/Enemy.h"
#include "../include/Food.h"
#include "../include/RestrictedRoom.h"

TEST(RestrictedRoomTest, RestrictedRoomTest) {
  Enemy *e = new Enemy("testEnemy", 1, "testDesc");
  Food *poison = new Food("testFood", -100);
  RestrictedRoom *rr =
      new RestrictedRoom("testRestrictedRoom", false, "testRoom", e);

  e->addItem(poison);

  EXPECT_EQ(e->isAlive(), true);
  EXPECT_EQ(rr->isAccessable(), false);

  // kill enemy
  e->useItem(poison);

  EXPECT_EQ(e->isAlive(), false);
  EXPECT_EQ(rr->isAccessable(), true);

  delete e;
  delete rr;
}

TEST(RestrictedRoomTest, GetRestrictedRoomTest) {
  Enemy *e = new Enemy("testEnemy", 1, "testDesc");
  Food *poison = new Food("testFood", -100);
  RestrictedRoom *rr =
      new RestrictedRoom("testRestrictedRoom", false, "testRoom", e);
  Room *r = new Room("restRoom", "regular room");

  r->setSouth(rr);

  e->addItem(poison);

  EXPECT_EQ(e->isAlive(), true);
  EXPECT_EQ(rr->isAccessable(), false);
  EXPECT_EQ(rr->getNorth(), r);
  EXPECT_EQ(r->getSouth()->isAccessable(), false);

  // kill enemy
  e->useItem(poison);

  EXPECT_EQ(e->isAlive(), false);
  EXPECT_EQ(rr->isAccessable(), true);
  EXPECT_EQ(rr->getNorth(), r);
  EXPECT_EQ(r->getSouth()->isAccessable(), true);

  delete e;
  delete r;
  delete rr;
}
