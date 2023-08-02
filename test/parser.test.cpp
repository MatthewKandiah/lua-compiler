#include "gtest/gtest.h"
#include <sstream>
#include "../src/parser.h"
#include "../src/astNode.h"

TEST(ParserTests, ShouldReturnNullPointerIfEOF) {
  std::istringstream inputStream {""};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result, nullptr);
}

TEST(ParserTests, ShouldParseSingleIntegerExpression) {
  std::istringstream inputStream {"1"};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "1");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseSingleMultiDigitIntegerExpressions) {
  std::istringstream inputStream {"12345"};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "12345");
}

TEST(ParserTests, ShouldParseSingleCharacterIdentifier) {
  std::istringstream inputStream {"a"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseMultiCharacterIdentifier) {
  std::istringstream inputStream {"arst"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "arst");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseIdentifierContainingNumbers) {
  std::istringstream inputStream {"a1r2s3t"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a1r2s3t");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(DebuggingTests, ShouldGetCorrectTokens) {
  std::istringstream inputStream {"1+a"};
  auto lexer = Lexer();

  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::integer);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::plus);
  EXPECT_EQ(lexer.getNextToken(inputStream).type, TokenType::identifier);

}

// okay, now we can see we're getting the correct tokens, so we must have an actual issue with the parsing logic
TEST(ParserTests, ShouldParsePlusExpression) {
  std::istringstream inputStream {"1+a"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->value, "+");
}

