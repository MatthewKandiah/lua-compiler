#include "gtest/gtest.h"
#include "../src/lexer.h"
#include <memory>
#include <sstream>

TEST(LexerTests, ShouldReturnEqualsToken) {
	std::istringstream inputStream('=');
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::equals); // failing - getting an illegal token instead
}

