#include "../src/lexer.h"

#include <memory>
#include <sstream>

#include "gtest/gtest.h"

TEST(LexerTests, ShouldReturnEqualsToken) {
  std::istringstream inputStream{"="};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::equals);
}

TEST(LexerTests, ShouldReturnPlusToken) {
  std::istringstream inputStream{"+"};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::plus);
}

TEST(LexerTests, ShouldReturnMinusToken) {
  std::istringstream inputStream{"-"};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::minus);
}

TEST(LexerTests, ShouldReturnLeftBracketToken) {
  std::istringstream inputStream{"("};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::leftBracket);
}

TEST(LexerTests, ShouldReturnRightBracketToken) {
  std::istringstream inputStream{")"};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldSkipOverInitialWhitespace) {
  std::istringstream inputStream{"   )"};
  auto result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldConsumeTokensAsTheyAreRead) {
  std::istringstream inputStream{"=+-()"};
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::equals);
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::plus);
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::minus);
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::leftBracket);
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldReturnEOFToken) {
  std::istringstream inputStream{""};
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::eof);
}

TEST(LexerTests, ShouldHandleAllWhitespaceInput) {
  std::istringstream inputStream("\n\t   \t\n");
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::eof);
}

