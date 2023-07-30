#include "parser.h"
#include <istream>
#include "tokenType.h"
#include "parserException.h"

void Parser::getNextToken(std::istream& inputStream) { currentToken = lexer.getNextToken(inputStream); }

std::unique_ptr<ExpressionAstNode> Parser::parseIntegerExpression(std::istream& inputStream) {
  if (currentToken.type != TokenType::integer) {
    throw InvalidTokenTypeException(TokenType::integer, currentToken.type, currentToken.value);
  }

  std::int64_t number = std::stoll(currentToken.value);
  auto result = std::make_unique<NumberExpressionAstNode>(number);
  getNextToken(inputStream);
  return std::move(result);
}



