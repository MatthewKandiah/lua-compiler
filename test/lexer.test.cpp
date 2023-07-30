#include "../src/lexer.h"

#include <memory>
#include <sstream>
#include <vector>

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

TEST(LexerTests, ShouldHandleIllegalToken) {
  std::istringstream inputStream("Š");
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::illegal);
}

TEST(LexerTests, ShouldHandleSingleCharacterIdentifiers) {
  std::istringstream inputStream("a");
  Token result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::identifier);
  EXPECT_EQ(result.value, "a");
}

TEST(LexerTests, ShouldHandleMultiChararcterIdentifiers) {
  std::istringstream inputStream("abcdef");
  Token result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::identifier);
  EXPECT_EQ(result.value, "abcdef");
}

TEST(LexerTests, ShouldSplitIdentifiersAtWhitespace) {
  std::istringstream inputStream("a bc def");

  Token result1 = Lexer().getNextToken(inputStream);
  Token result2 = Lexer().getNextToken(inputStream);
  Token result3 = Lexer().getNextToken(inputStream);

  EXPECT_EQ(result1.value, "a");
  EXPECT_EQ(result2.value, "bc");
  EXPECT_EQ(result3.value, "def");
}

TEST(LexerTests, ShouldHandleLocalKeyword) {
  std::istringstream inputStream("local");
  EXPECT_EQ(Lexer().getNextToken(inputStream).type, TokenType::local);
}

TEST(LexerTests, ShouldHandleLocalKeywordAndIdentifiers) {
  std::istringstream inputStream("a local b local local c d local");
  std::vector<Token> results{};
  while (inputStream) {
    results.push_back(Lexer().getNextToken(inputStream));
  }

  EXPECT_EQ(results.size(), 8);
  EXPECT_EQ(results[0].type, TokenType::identifier);
  EXPECT_EQ(results[1].type, TokenType::local);
  EXPECT_EQ(results[2].type, TokenType::identifier);
  EXPECT_EQ(results[3].type, TokenType::local);
  EXPECT_EQ(results[4].type, TokenType::local);
  EXPECT_EQ(results[5].type, TokenType::identifier);
  EXPECT_EQ(results[6].type, TokenType::identifier);
  EXPECT_EQ(results[7].type, TokenType::local);
}

TEST(LexerTests, ShouldHandleSingleDigitInteger) {
  std::istringstream inputStream("1");
  Token result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::integer);
  EXPECT_EQ(result.value, "1");
}

TEST(LexerTests, ShouldHandleMultiDigitIntegers) {
  std::istringstream inputStream("123456");
  Token result = Lexer().getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::integer);
  EXPECT_EQ(result.value, "123456");
}

TEST(LexerTests, ShouldHandleMultipleIntegers) {
  std::istringstream inputStream("1 23 456 7890");
  Token result1 = Lexer().getNextToken(inputStream);
  Token result2 = Lexer().getNextToken(inputStream);
  Token result3 = Lexer().getNextToken(inputStream);
  Token result4 = Lexer().getNextToken(inputStream);

  EXPECT_EQ(result1.value, "1");
  EXPECT_EQ(result2.value, "23");
  EXPECT_EQ(result3.value, "456");
  EXPECT_EQ(result4.value, "7890");
}
