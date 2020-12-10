#include "gtest/gtest.h"
#include "../src/Coord.hpp"

TEST(mainTest, ThisTestShallFail)
{
     Coord *c = new Coord(1, 2);
     Coord *d = new Coord(1, 2);
     // Some operations here
     EXPECT_EQ(c->x(), d->x());
}