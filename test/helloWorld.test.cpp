#include "gtest/gtest.h"
#include <iostream>
#include "../src/helloWorld.h"

TEST(TestTests, TestThatPasses) {
	auto x = makeString();
	EXPECT_EQ(x, "Hello, World!");
}	

TEST(TestTests, TestThatFails) {
	auto x = makeString();
	EXPECT_EQ(x,"Goodbye, Loser!");
}
