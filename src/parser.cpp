#include "parser.h"
#include "astNode.h"
#include "lexer.h"
#include <istream>

Token Parser::getNextToken(std::istream &inputStream) {
  return Lexer().getNextToken(inputStream);
};
AstExpressionNode Parser::parseExpression(std::istream &inputStream) {
  return AstExpressionNode(AstNodeType::variable, "incorrect", nullptr, nullptr);
};
