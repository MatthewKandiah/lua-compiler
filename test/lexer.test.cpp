#include "../src/lexer.h"

#include <memory>
#include <sstream>
#include <sys/syslimits.h>
#include <vector>

#include "gtest/gtest.h"

TEST(LexerTests, ShouldReturnEqualsToken) {
  std::istringstream inputStream{"="};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::equals);
}

TEST(LexerTests, ShouldReturnPlusToken) {
  std::istringstream inputStream{"+"};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::plus);
}

TEST(LexerTests, ShouldReturnMinusToken) {
  std::istringstream inputStream{"-"};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::minus);
}

TEST(LexerTests, ShouldReturnLeftBracketToken) {
  std::istringstream inputStream{"("};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::leftBracket);
}

TEST(LexerTests, ShouldReturnRightBracketToken) {
  std::istringstream inputStream{")"};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldSkipOverInitialWhitespace) {
  std::istringstream inputStream{"   )"};
  auto lexer = Lexer();
  auto result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldConsumeTokensAsTheyAreRead) {
  std::istringstream inputStream{"=+-()"};
  auto lexer = Lexer();
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::equals);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::plus);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::minus);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::leftBracket);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::rightBracket);
}

TEST(LexerTests, ShouldReturnEOFToken) {
  std::istringstream inputStream{""};
  auto lexer = Lexer();
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::eof);
}

TEST(LexerTests, ShouldHandleAllWhitespaceInput) {
  std::istringstream inputStream("\n\t   \t\n");
  auto lexer = Lexer();
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::eof);
}

TEST(LexerTests, ShouldHandleIllegalToken) {
  std::istringstream inputStream("Š");
  auto lexer = Lexer();
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::illegal);
}

TEST(LexerTests, ShouldHandleSingleCharacterIdentifiers) {
  std::istringstream inputStream("a");
  auto lexer = Lexer();
  Token result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::identifier);
  EXPECT_EQ(result.value, "a");
}

TEST(LexerTests, ShouldHandleMultiChararcterIdentifiers) {
  std::istringstream inputStream("abcdef");
  auto lexer = Lexer();
  Token result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::identifier);
  EXPECT_EQ(result.value, "abcdef");
}

TEST(LexerTests, ShouldSplitIdentifiersAtWhitespace) {
  std::istringstream inputStream("a bc def");

  auto lexer = Lexer();
  Token result1 = lexer.getNextToken(inputStream);
  Token result2 = lexer.getNextToken(inputStream);
  Token result3 = lexer.getNextToken(inputStream);

  EXPECT_EQ(result1.value, "a");
  EXPECT_EQ(result2.value, "bc");
  EXPECT_EQ(result3.value, "def");
}

TEST(LexerTests, ShouldHandleLocalKeyword) {
  std::istringstream inputStream("local");
  auto lexer = Lexer();
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::local);
}

TEST(LexerTests, ShouldHandleLocalKeywordAndIdentifiers) {
  std::istringstream inputStream("a local b local local c d local");
  std::vector<Token> results{};
  auto lexer = Lexer();
  while (inputStream) {
    results.push_back(lexer.getNextToken(inputStream));
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
  auto lexer = Lexer();
  Token result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::integer);
  EXPECT_EQ(result.value, "1");
}

TEST(LexerTests, ShouldHandleMultiDigitIntegers) {
  std::istringstream inputStream("123456");
  auto lexer = Lexer();
  Token result = lexer.getNextToken(inputStream);
  EXPECT_EQ(result.type, TokenType::integer);
  EXPECT_EQ(result.value, "123456");
}

TEST(LexerTests, ShouldHandleMultipleIntegers) {
  std::istringstream inputStream("1 23 456 7890");
  auto lexer = Lexer();
  Token result1 = lexer.getNextToken(inputStream);
  Token result2 = lexer.getNextToken(inputStream);
  Token result3 = lexer.getNextToken(inputStream);
  Token result4 = lexer.getNextToken(inputStream);

  EXPECT_EQ(result1.value, "1");
  EXPECT_EQ(result2.value, "23");
  EXPECT_EQ(result3.value, "456");
  EXPECT_EQ(result4.value, "7890");
}

TEST(LexerTests, ShouldHandleMixOfSymbolsIntegersIdentifiersAndSpaces) {
  std::istringstream inputStream {"1 + a - 12+5-b"};
  auto lexer = Lexer();
  Token result1 = lexer.getNextToken(inputStream);
  Token result2 = lexer.getNextToken(inputStream);
  Token result3 = lexer.getNextToken(inputStream);
  Token result4 = lexer.getNextToken(inputStream);
  Token result5 = lexer.getNextToken(inputStream);
  Token result6 = lexer.getNextToken(inputStream);
  Token result7 = lexer.getNextToken(inputStream);
  Token result8 = lexer.getNextToken(inputStream);
  Token result9 = lexer.getNextToken(inputStream);

  EXPECT_EQ(result1.type, TokenType::integer);
  EXPECT_EQ(result2.type, TokenType::plus);
  EXPECT_EQ(result3.type, TokenType::identifier);
  EXPECT_EQ(result4.type, TokenType::minus);
  EXPECT_EQ(result5.type, TokenType::integer);
  EXPECT_EQ(result6.type, TokenType::plus);
  EXPECT_EQ(result7.type, TokenType::integer);
  EXPECT_EQ(result8.type, TokenType::minus);
  EXPECT_EQ(result9.type, TokenType::identifier);
}
