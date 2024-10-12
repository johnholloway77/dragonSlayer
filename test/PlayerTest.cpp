//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/Player.h"

TEST(PlayerTest, defaultConstructorTest) {
  Player *p = new Player("testUser", 100);

  EXPECT_EQ(p->getName(), "testUser");
  EXPECT_EQ(p->getHealth(), 100);

  delete p;
}