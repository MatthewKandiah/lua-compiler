#include "parser.h"
#include <istream>
#include "tokenType.h"
#include "parserException.h"
#include "astNode.h"

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

std::unique_ptr<ExpressionAstNode> Parser::parseIdentifierExpression(std::istream& inputStream) {
  if (currentToken.type != TokenType::identifier) {
    throw InvalidTokenTypeException(TokenType::identifier, currentToken.type, currentToken.value);
  }

  std::string name = currentToken.value;
  auto result = std::make_unique<VariableExpressionAstNode>(name);
  getNextToken(inputStream);
  return std::move(result);
}

