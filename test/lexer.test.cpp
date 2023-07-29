#include "gtest/gtest.h"
#include "../src/lexer.h"
#include <memory>
#include <sstream>

TEST(LexerTests, ShouldReturnEqualsToken) {
	std::istringstream inputStream {"="};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::equals);
}

TEST(LexerTests, ShouldReturnPlusToken) {
	std::istringstream inputStream {"+"};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::plus);
}

TEST(LexerTests, ShouldReturnMinusToken) {
	std::istringstream inputStream {"-"};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::minus);
}

TEST(LexerTests, ShouldReturnLeftBracketToken) {
	std::istringstream inputStream {"("};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::leftBracket);
}

TEST(LexerTests, ShouldReturnRightBracketToken) {
	std::istringstream inputStream {")"};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldSkipOverInitialWhitespace) {
	std::istringstream inputStream {"   )"};
	Lexer lexer(&inputStream);

	auto result = lexer.getNextToken();

	EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldConsumeTokensAsTheyAreRead) {
	std::istringstream inputStream {"=+-()"};
	Lexer lexer(&inputStream);

	EXPECT_EQ(lexer.getNextToken().type, TokenType::equals);
	EXPECT_EQ(lexer.getNextToken().type, TokenType::plus);
	EXPECT_EQ(lexer.getNextToken().type, TokenType::minus);
	EXPECT_EQ(lexer.getNextToken().type, TokenType::leftBracket);
	EXPECT_EQ(lexer.getNextToken().type, TokenType::rightBracket);
}

