#include "gtest/gtest.h"
#include <sstream>
#include "../src/parser.h"
#include "../src/astNode.h"

TEST(ParserTests, ShouldParseSingleIntegerExpression) {
  std::istringstream inputStream {"1"};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result.type, AstNodeType::integer);
  EXPECT_EQ(result.value, "1");
  EXPECT_EQ(result.lhs, nullptr);
  EXPECT_EQ(result.rhs, nullptr);
}

TEST(ParserTests, ShouldParseSingleMultiDigitIntegerExpressions) {
  std::istringstream inputStream {"12345"};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result.type, AstNodeType::integer);
  EXPECT_EQ(result.value, "12345");
}

TEST(ParserTests, ShouldParseSingleCharacterIdentifier) {
  std::istringstream inputStream {"a"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result.type, AstNodeType::variable);
  EXPECT_EQ(result.value, "a");
  EXPECT_EQ(result.lhs, nullptr);
  EXPECT_EQ(result.rhs, nullptr);
}

TEST(ParserTests, ShouldParseMultiCharacterIdentifier) {
  std::istringstream inputStream {"arst"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result.type, AstNodeType::variable);
  EXPECT_EQ(result.value, "arst");
  EXPECT_EQ(result.lhs, nullptr);
  EXPECT_EQ(result.rhs, nullptr);
}

TEST(ParserTests, ShouldParseIdentifierContainingNumbers) {
  std::istringstream inputStream {"a1r2s3t"};

  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);

  EXPECT_EQ(result.type, AstNodeType::variable);
  EXPECT_EQ(result.value, "a1r2s3t");
  EXPECT_EQ(result.lhs, nullptr);
  EXPECT_EQ(result.rhs, nullptr);
}

