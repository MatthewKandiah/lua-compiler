#include "../src/parser.h"
#include "../src/astNode.h"
#include "../src/lexer.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>
#include <vector>

TEST(ParserTests, ShouldReturnNullPointerIfEOF) {
  std::istringstream inputStream{""};
  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser {std::move(lexer)};
  auto result = parser.parseExpression();
  EXPECT_EQ(result, nullptr);
}

TEST(ParserTests, ShouldParseSingleIntegerExpression) {
  std::istringstream inputStream{"1"};
  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "1");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseSingleMultiDigitIntegerExpressions) {
  std::istringstream inputStream{"12345"};
  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "12345");
}

TEST(ParserTests, ShouldParseSingleCharacterIdentifier) {
  std::istringstream inputStream{"a"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseMultiCharacterIdentifier) {
  std::istringstream inputStream{"arst"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "arst");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseIdentifierContainingNumbers) {
  std::istringstream inputStream{"a1r2s3t"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a1r2s3t");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParsePlusExpression) {
  std::istringstream inputStream{"1+a"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->value, "+");
  EXPECT_EQ(result->lhs->type, AstNodeType::integer);
  EXPECT_EQ(result->lhs->value, "1");
  EXPECT_EQ(result->rhs->type, AstNodeType::variable);
  EXPECT_EQ(result->rhs->value, "a");
}

TEST(ParserTests, ShouldParseMinusExpression) {
  std::istringstream inputStream{"b-2"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->value, "-");
  EXPECT_EQ(result->lhs->type, AstNodeType::variable);
  EXPECT_EQ(result->lhs->value, "b");
  EXPECT_EQ(result->rhs->type, AstNodeType::integer);
  EXPECT_EQ(result->rhs->value, "2");
}

TEST(ParserTests, ShouldParseEqualsExpression) {
  std::istringstream inputStream{"Z=26"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->value, "=");
  EXPECT_EQ(result->lhs->type, AstNodeType::variable);
  EXPECT_EQ(result->lhs->value, "Z");
  EXPECT_EQ(result->rhs->type, AstNodeType::integer);
  EXPECT_EQ(result->rhs->value, "26");
}

TEST(ParserTest, ShouldParseNestedBinaryExpressions) {
  std::istringstream inputStream{"foo = 17 + bar"};

  auto lexer = std::make_unique<Lexer>(inputStream);
  Parser parser{std::move(lexer)};
  auto result = parser.parseExpression();

  EXPECT_EQ(result->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->value, "=");

  EXPECT_EQ(result->lhs->type, AstNodeType::variable);
  EXPECT_EQ(result->lhs->value, "foo");

  EXPECT_EQ(result->rhs->type, AstNodeType::binaryOperator);
  EXPECT_EQ(result->rhs->value, "+");

  EXPECT_EQ(result->rhs->lhs->type, AstNodeType::integer);
  EXPECT_EQ(result->rhs->lhs->value, "17");

  EXPECT_EQ(result->rhs->rhs->type, AstNodeType::variable);
  EXPECT_EQ(result->rhs->rhs->value, "bar");
}
