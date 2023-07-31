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

TEST(ParserTests, ShouldParseMultipleIntegerExpressions) {
  std::istringstream inputStream {"1 2 3 4 5"};

  auto parser = Parser(inputStream);
  auto result1 = parser.parseExpression(inputStream);
  auto result2 = parser.parseExpression(inputStream);
  auto result3 = parser.parseExpression(inputStream);
  auto result4 = parser.parseExpression(inputStream);
  auto result5 = parser.parseExpression(inputStream);

  EXPECT_EQ(result1.type, AstNodeType::integer);
  EXPECT_EQ(result1.value, "1");
  EXPECT_EQ(result2.type, AstNodeType::integer);
  EXPECT_EQ(result2.value, "2");
  EXPECT_EQ(result3.type, AstNodeType::integer);
  EXPECT_EQ(result3.value, "3");
  EXPECT_EQ(result4.type, AstNodeType::integer);
  EXPECT_EQ(result4.value, "4");
  EXPECT_EQ(result5.type, AstNodeType::integer);
  EXPECT_EQ(result5.value, "5");
}

TEST(ParserTests, ShouldParseSingleMultiDigitIntegerExpressions) {
  std::istringstream inputStream {"12345"};
  auto parser = Parser(inputStream);
  auto result = parser.parseExpression(inputStream);
  EXPECT_EQ(result.type, AstNodeType::integer);
  EXPECT_EQ(result.value, "12345");
}

TEST(ParserTests, ShouldParseMultipleMultiDigitIntegerExpressions) {
  std::istringstream inputStream {"123 234 345"};

  auto parser = Parser(inputStream);
  auto result1 = parser.parseExpression(inputStream);
  auto result2 = parser.parseExpression(inputStream);
  auto result3 = parser.parseExpression(inputStream);

  EXPECT_EQ(result1.type, AstNodeType::integer);
  EXPECT_EQ(result1.value, "123");
  EXPECT_EQ(result2.type, AstNodeType::integer);
  EXPECT_EQ(result2.value, "234");
  EXPECT_EQ(result3.type, AstNodeType::integer);
  EXPECT_EQ(result3.value, "345");
}

