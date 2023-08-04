#include "parser.h"
#include "astNode.h"
#include "lexer.h"
#include "tokenType.h"
#include <cstdint>
#include <exception>
#include <iostream>
#include <istream>
#include <memory>

Token Parser::getNextToken(std::istream &inputStream) {
  auto result = lexer.getNextToken(inputStream);
  return result;
};

std::unique_ptr<AstExpressionNode> Parser::parseExpression(std::istream &inputStream) {
  auto lhs = parsePrimaryExpression(inputStream);
  if (!lhs) return nullptr;
  return parseBinaryExpressionRhs(inputStream, 0, std::move(lhs));
};

std::unique_ptr<AstExpressionNode> Parser::parseBinaryExpressionRhs(std::istream &inputStream, std::int64_t expressionPrecedence, std::unique_ptr<AstExpressionNode> lhs) {
  while(true) {
    std::int64_t tokenPrecedence = getOperatorPrecedence(currentToken.value);
    if (tokenPrecedence < expressionPrecedence) {
      // next token is lower precedence than the current expression, so we can safely calculate the value of the current expression without looking at it
      std::cerr << "return lhs " << lhs->value << '\n';
      return lhs;
    }
    Token binaryOperator = currentToken;
    currentToken = getNextToken(inputStream);
    auto rhs = parsePrimaryExpression(inputStream);
    if (!rhs) return nullptr;

    std::int64_t nextTokenPrecedence = getOperatorPrecedence(currentToken.value);
    if (tokenPrecedence < nextTokenPrecedence) {
      // next token is higher precedence and needs to be calculated first, then its value passed in as the rhs of this binary expression
      rhs = parseBinaryExpressionRhs(inputStream, tokenPrecedence + 1, std::move(rhs));
    }
    // next token is equal / lower precedence, we can just calculate the value of this expression now and pass the value into the next operator
    lhs = std::make_unique<AstExpressionNode>(AstNodeType::binaryOperator, binaryOperator.value, std::move(lhs), std::move(rhs));
  }
}

std::unique_ptr<AstExpressionNode> Parser::parsePrimaryExpression(std::istream &inputStream) {
  std::unique_ptr<AstExpressionNode> result;
  switch(currentToken.type) {
    case TokenType::integer:
      result = std::make_unique<AstExpressionNode>(AstNodeType::integer, currentToken.value, nullptr, nullptr);
      break;
    case TokenType::identifier:
      result = std::make_unique<AstExpressionNode>(AstNodeType::variable, currentToken.value, nullptr, nullptr);
      break;
    case TokenType::eof:
    case TokenType::illegal:
    case TokenType::equals:
    case TokenType::plus:
    case TokenType::minus:
    case TokenType::leftBracket:
    case TokenType::rightBracket:
    case TokenType::local:
      result = nullptr;
      break;
  }
  currentToken = getNextToken(inputStream);
  return result;
}

std::int64_t Parser::getOperatorPrecedence(std::string opString) {
  // BUG - we're passing in the value, which is "" for all operators, so we always return -1?!
  if (opString.length() == 0) return -1;
  char op = opString[0];
  switch(op){
    case '+':
    case '-':
      return 10;
    case '=':
      return 0;
    default:
      return -1;
  }
};

