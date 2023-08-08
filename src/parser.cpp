#include "parser.h"
#include "astNode.h"
#include "lexer.h"
#include "tokenType.h"
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>

std::unique_ptr<AstExpressionNode> Parser::parseExpression() {
  auto lhs = parsePrimaryExpression();
  if (!lhs) return nullptr;
  return parseBinaryExpressionRhs(0, std::move(lhs));
};

std::unique_ptr<AstExpressionNode> Parser::parseBinaryExpressionRhs(std::int64_t expressionPrecedence, std::unique_ptr<AstExpressionNode> lhs) {
  while(true) {
    std::int64_t tokenPrecedence = getOperatorPrecedence(currentToken);
    if (tokenPrecedence < expressionPrecedence) {
      // next token is lower precedence than the current expression, so we can safely calculate the value of the current expression without looking at it
      return lhs;
    }
    Token binaryOperator = currentToken;
    currentToken = lexer.getNextToken();
    auto rhs = parsePrimaryExpression();
    if (!rhs) return nullptr;

    std::int64_t nextTokenPrecedence = getOperatorPrecedence(currentToken);
    if (tokenPrecedence < nextTokenPrecedence) {
      // next token is higher precedence and needs to be calculated first, then its value passed in as the rhs of this binary expression
      rhs = parseBinaryExpressionRhs(tokenPrecedence + 1, std::move(rhs));
    }
    // next token is equal / lower precedence, we can just calculate the value of this expression now and pass the value into the next operator
    lhs = std::make_unique<AstExpressionNode>(AstNodeType::binaryOperator, tokenTypeToBinaryOperatorString(binaryOperator.type), std::move(lhs), std::move(rhs));
  }
}

std::unique_ptr<AstExpressionNode> Parser::parsePrimaryExpression() {
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
  currentToken = lexer.getNextToken();
  return result;
}

std::int64_t Parser::getOperatorPrecedence(Token token) {
  // higher precedence operators are done before lower precedence operators
  switch(token.type){
    case TokenType::plus:
    case TokenType::minus:
      return 10;
    case TokenType::equals:
      return 0;
    default:
      return -1;
  }
};

std::string Parser::tokenTypeToBinaryOperatorString(TokenType tokenType) {
  switch (tokenType) {
    case TokenType::plus:
      return "+";
    case TokenType::minus:
      return "-";
    case TokenType::equals:
      return "=";
    case TokenType::eof:
    case TokenType::illegal:
    case TokenType::identifier:
    case TokenType::integer:
    case TokenType::leftBracket:
    case TokenType::rightBracket:
    case TokenType::local:
      return "";
    }
}

