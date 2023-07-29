#include "gtest/gtest.h"

TEST(TestTests, TestThatPasses) {
	EXPECT_EQ(1, 1);
}	

TEST(TestTests, TestThatFails) {
	EXPECT_EQ(1, 2);
}
