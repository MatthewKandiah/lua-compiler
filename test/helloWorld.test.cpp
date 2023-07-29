#include "gtest/gtest.h"
#include <iostream>
#include "../include/lua-compiler/helloWorld.h"

TEST(TestTests, TestThatPasses) {
	auto x = makeString();
	EXPECT_EQ(x, "Hello, World!");
}	

TEST(TestTests, TestThatFails) {
	auto y = makeString();
	EXPECT_EQ(y,"Goodbye, Loser!");
}
