#include "../src/astNode.h"
#include "../src/parser.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>

TEST(WatGeneratorTests, DoesMyMockParserBlowUp) {
  auto expression1 = std::unique_ptr<AstExpressionNode>(new AstExpressionNode(AstNodeType::integer, std::string("2"), nullptr, nullptr));
  auto expression2 = std::unique_ptr<AstExpressionNode>(new AstExpressionNode(AstNodeType::variable, std::string("ant"), nullptr, nullptr));

  std::vector<std::unique_ptr<AstExpressionNode>> expressions{};
  expressions.push_back(std::move(expression1));
  expressions.push_back(std::move(expression2));

  MockParser parser {std::move(expressions)};
  auto firstExpression = parser.parseExpression();
  auto secondExpression = parser.parseExpression();
  EXPECT_EQ(firstExpression->type, AstNodeType::integer);
  EXPECT_EQ(firstExpression->value, "2");
  EXPECT_EQ(firstExpression->lhs, nullptr);
  EXPECT_EQ(firstExpression->rhs, nullptr);
  EXPECT_EQ(secondExpression->type, AstNodeType::variable);
  EXPECT_EQ(secondExpression->value, "ant");
  EXPECT_EQ(secondExpression->lhs, nullptr);
  EXPECT_EQ(secondExpression->rhs, nullptr);
};
