#include <cstdint>
#include <memory>
#include <string>
class ExpressionAstNode {};

class NumberExpressionAstNode : public ExpressionAstNode {
 public:
  NumberExpressionAstNode(std::int64_t v) : val{v} {};
  std::int64_t val;
};

class VariableExpressionAstNode : public ExpressionAstNode {
 public:
  VariableExpressionAstNode(const std::string& n) : name{n} {};
  std::string name;
};

class BinaryExpressionAstNode : public ExpressionAstNode {
 public:
  BinaryExpressionAstNode(char o, std::unique_ptr<ExpressionAstNode> l, std::unique_ptr<ExpressionAstNode> r)
      : op{o}, lhs{std::move(l)}, rhs{std::move(r)} {};
  char op;
  std::unique_ptr<ExpressionAstNode> lhs, rhs;
};

