#include "../src/watGenerator.h"
#include "../src/astNode.h"
#include "../src/parser.h"
#include "gtest/gtest.h"
#include <memory>
#include <sstream>
#include <string>
#include <vector>

TEST(WatGeneratorTests, ShouldGenerateValidEmptyModule) {
  auto output = std::make_shared<std::ostringstream>("");
  std::vector<std::unique_ptr<AstExpressionNode>> expressions{};
  auto parser = std::make_unique<MockParser>(std::move(expressions));
  WatGenerator generator{output, std::move(parser)};

  generator.generate();

  auto result = output->str();
  EXPECT_EQ(result, "(module )");
};

TEST(WatGeneratorTests, ShouldGenerateAnAddExpression){};

TEST(WatGeneratorTests, ShouldGenerateAMinusExpression){};

TEST(WatGeneratorTests, ShouldGenerateAnAssignment){};
