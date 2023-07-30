#include "parser.h"
#include "astNode.h"
#include "parserException.h"
#include "tokenType.h"
#include <cstdint>
#include <istream>
#include <memory>

void Parser::getNextToken(std::istream &inputStream) {
  currentToken = lexer.getNextToken(inputStream);
}

std::unique_ptr<ExpressionAstNode>
Parser::parseExpression(std::istream &inputStream) {
  auto lhs = parsePrimaryExpression(inputStream);
  if (!lhs) {
    throw FailedToParseExpressionException();
  }

  return parseBinaryExpression(inputStream, 0, std::move(lhs));
}

std::unique_ptr<ExpressionAstNode>
Parser::parsePrimaryExpression(std::istream &inputStream) {
  switch (currentToken.type) {
  case TokenType::identifier:
    parseIdentifierExpression(inputStream);
  case TokenType::integer:
    parseIntegerExpression(inputStream);
  case TokenType::equals:
  case TokenType::plus:
  case TokenType::minus:
    // parse binary op
  case TokenType::eof:
    // handle eof sensibly, or maybe drop eof token?
  case TokenType::illegal:
  case TokenType::leftBracket:
  case TokenType::rightBracket:
  case TokenType::local:
    throw UnexpectedTokenException(currentToken);
  }
}

std::unique_ptr<ExpressionAstNode>
Parser::parseBinaryExpression(std::istream &inputStream,
                              std::int64_t expressionPrecedence,
                              std::unique_ptr<ExpressionAstNode> lhs) {
  while (true) {
    std::int64_t tokenPrecedence = getTokenPrecedence(currentToken);
    if (tokenPrecedence < expressionPrecedence) {
      return lhs;
    }

    char binaryOperatorCharacter = static_cast<char>(currentToken.value[0]);
    getNextToken(inputStream);
    auto rhs = parsePrimaryExpression(inputStream);
    // parsing primary expression consumes that token, so current token may be
    // another operator
    std::int64_t nextTokenPrecedence = getTokenPrecedence(currentToken);
    if (tokenPrecedence < nextTokenPrecedence) {
      // next operator is higher precedence, so it will act before this operator
      // does
      rhs = parseBinaryExpression(inputStream, tokenPrecedence + 1,
                                  std::move(rhs));
      if (!rhs) {
        throw FailedToParseExpressionException();
      }
    }
    // next operator is lower precedence, so it will act after this operator
    // does
    lhs = std::make_unique<BinaryExpressionAstNode>(
        binaryOperatorCharacter, std::move(lhs), std::move(rhs));
  }
}

std::int64_t Parser::getTokenPrecedence(Token token) {
  switch (token.type) {
  case TokenType::plus:
  case TokenType::minus:
    return 20;
  case TokenType::eof:
  case TokenType::illegal:
  case TokenType::identifier:
  case TokenType::integer:
  case TokenType::equals:
  case TokenType::leftBracket:
  case TokenType::rightBracket:
  case TokenType::local:
    return -1;
  }
}

std::unique_ptr<ExpressionAstNode>
Parser::parseIntegerExpression(std::istream &inputStream) {
  if (currentToken.type != TokenType::integer) {
    throw InvalidTokenTypeException(TokenType::integer, currentToken.type,
                                    currentToken.value);
  }

  std::int64_t number = std::stoll(currentToken.value);
  auto result = std::make_unique<NumberExpressionAstNode>(number);
  getNextToken(inputStream);
  return std::move(result);
}

std::unique_ptr<ExpressionAstNode>
Parser::parseIdentifierExpression(std::istream &inputStream) {
  if (currentToken.type != TokenType::identifier) {
    throw InvalidTokenTypeException(TokenType::identifier, currentToken.type,
                                    currentToken.value);
  }

  std::string name = currentToken.value;
  auto result = std::make_unique<VariableExpressionAstNode>(name);
  getNextToken(inputStream);
  return std::move(result);
}
