#include "gtest/gtest.h"

int cubic(int i)
{
    return i*i*i;
}

TEST(testMath, myCubeTest)
{
    EXPECT_EQ(1000, cubic(10));
}
