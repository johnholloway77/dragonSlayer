//
// "Copyright [2024] J. Holloway, Dorgee Lama, and John Nisperos"
//

#include <gtest/gtest.h>

#include "../include/ExitRoom.h"

TEST(ExitRoomTest, defaultConstructorTest) {
  ExitRoom *e = new ExitRoom("testExitRoom", "A test exitRoom");

  EXPECT_EQ(e->getName(), "testExitRoom");
  EXPECT_EQ(e->getDescription(), "A test exitRoom");

  delete e;
}
