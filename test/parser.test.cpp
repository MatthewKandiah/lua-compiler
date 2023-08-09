#include "../src/parser.h"
#include "../src/astNode.h"
#include "../src/lexer.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>
#include <vector>

TEST(ParserTests, ShouldReturnNullPointerIfEOF) {
  Token token {TokenType::eof, ""};
  std::vector<Token> tokens {token};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser {std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result, nullptr);
}

TEST(ParserTests, ShouldParseSingleIntegerExpression) {
  Token token1 {TokenType::integer, "1"};
  Token token2 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser{std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "1");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseSingleMultiDigitIntegerExpressions) {
  Token token1 {TokenType::integer, "12345"};
  Token token2 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser{std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::integer);
  EXPECT_EQ(result->value, "12345");
}

TEST(ParserTests, ShouldParseSingleCharacterIdentifier) {
  Token token1 {TokenType::identifier, "a"};
  Token token2 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser{std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseMultiCharacterIdentifier) {
  Token token1 {TokenType::identifier, "arst"};
  Token token2 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser{std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "arst");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParseIdentifierContainingNumbers) {
  Token token1 {TokenType::identifier, "a1r2s3t"};
  Token token2 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2};
  auto lexer = std::make_unique<MockLexer>(tokens);
  Parser parser{std::move(lexer)};

  auto result = parser.parseExpression();
  EXPECT_EQ(result->type, AstNodeType::variable);
  EXPECT_EQ(result->value, "a1r2s3t");
  EXPECT_EQ(result->lhs, nullptr);
  EXPECT_EQ(result->rhs, nullptr);
}

TEST(ParserTests, ShouldParsePlusExpression) {
  Token token1 {TokenType::integer, "1"};
  Token token2 {TokenType::plus, ""};
  Token token3 {TokenType::identifier, "a"};
  Token token4 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2, token3, token4};
  auto lexer = std::make_unique<MockLexer>(tokens);
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
  Token token1 {TokenType::identifier, "b"};
  Token token2 {TokenType::minus, ""};
  Token token3 {TokenType::integer, "2"};
  Token token4 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2, token3, token4};
  auto lexer = std::make_unique<MockLexer>(tokens);
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
  Token token1 {TokenType::identifier, "Z"};
  Token token2 {TokenType::equals, ""};
  Token token3 {TokenType::integer, "26"};
  Token token4 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2, token3, token4};
  auto lexer = std::make_unique<MockLexer>(tokens);
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
  Token token1 {TokenType::identifier, "foo"};
  Token token2 {TokenType::equals, ""};
  Token token3 {TokenType::integer, "17"};
  Token token4 {TokenType::plus, ""};
  Token token5 {TokenType::identifier, "bar"};
  Token token6 {TokenType::eof, ""};
  std::vector<Token> tokens {token1, token2, token3, token4, token5, token6};
  auto lexer = std::make_unique<MockLexer>(tokens);
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
