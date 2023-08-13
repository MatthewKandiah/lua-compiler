#ifndef AST_NODE_H
#define AST_NODE_H

#include <cstdint>
#include <memory>
#include <string>

enum class AstNodeType {
  integer,
  variable,
  binaryOperator,
};

class AstExpressionNode {
public:
  AstExpressionNode(AstNodeType t, std::string v,
                    std::unique_ptr<AstExpressionNode> l,
                    std::unique_ptr<AstExpressionNode> r)
      : type{t}, value{v}, lhs{std::move(l)}, rhs{std::move(r)} {};
  AstNodeType type;
  std::string value;
  std::unique_ptr<AstExpressionNode> lhs, rhs;
};
#endif // !AST_NODE_H
