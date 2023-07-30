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
Parser::parseBinaryExpression(std::istream &inputStream, std::int64_t expressionPrecedence, std::unique_ptr<ExpressionAstNode> lhs) {
  while (true) {
    // continue here from https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl02.html
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
