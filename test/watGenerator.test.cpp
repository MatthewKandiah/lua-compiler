#include "../src/astNode.h"
#include "../src/parser.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>

TEST(WatGeneratorTests, DoesMyMockParserBlowUp) {
  auto expression1 = std::make_unique<AstExpressionNode>(
      AstNodeType::integer, std::string("2"), nullptr, nullptr);
  auto expression2 = std::make_unique<AstExpressionNode>(
      AstNodeType::variable, std::string("hello"), nullptr, nullptr);

  std::vector<std::unique_ptr<AstNodeType>> expressions{};
  // boom
  expressions.emplace_back(std::vector<std::unique_ptr<AstExpressionNode>>{
      std::move(expression1), std::move(expression2)});
  // TODO - we can't even check the MockParser is working until we can pass in this vector, clearly doing something daft!
  // MockParser mockParser{expressions};
};
