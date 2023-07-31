#include "parser.h"
#include "astNode.h"
#include "lexer.h"
#include "tokenType.h"
#include <exception>
#include <iostream>
#include <istream>

Token Parser::getNextToken(std::istream &inputStream) {
  return Lexer().getNextToken(inputStream);
};

AstExpressionNode Parser::parseExpression(std::istream &inputStream) {
  auto result = parsePrimaryExpression();
  currentToken = Lexer().getNextToken(inputStream);
  return result;
};

AstExpressionNode Parser::parsePrimaryExpression() {
  switch(currentToken.type) {
    case TokenType::integer:
      return AstExpressionNode(AstNodeType::integer, currentToken.value, nullptr, nullptr);
    case TokenType::identifier:
      return AstExpressionNode(AstNodeType::variable, currentToken.value, nullptr, nullptr);
    case TokenType::eof:
    case TokenType::illegal:
    case TokenType::equals:
    case TokenType::plus:
    case TokenType::minus:
    case TokenType::leftBracket:
    case TokenType::rightBracket:
    case TokenType::local:
      std::cerr << "Failed to parse token\n";
      throw std::exception();
  }
}

std::int64_t getOperatorPrecedence(char op) {
  switch(op){
    case '+':
    case '-':
      return 10;
    default:
      std::cerr << "Failed to get operator precedence\n";
      throw std::exception();
  }
};

