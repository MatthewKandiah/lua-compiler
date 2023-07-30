#ifndef PARSER_H
#define PARSER_H

#include <cstdint>
#include <istream>
#include <map>
#include <utility>

#include "astNode.h"
#include "lexer.h"
#include "token.h"
#include "tokenType.h"

class Parser {
 public:
  Parser(Lexer l, std::istream inputStream) : lexer{l}, currentToken{Token(TokenType::illegal, "")} {
    getNextToken(inputStream);
  }
  std::unique_ptr<ExpressionAstNode> parseExpression(std::istream&);

 private:
  Lexer lexer;
  Token currentToken;
  void getNextToken(std::istream&);
  const std::map<char, std::int64_t> binaryOperatorPrecedence {
    std::make_pair('+', 20),
    std::make_pair('-', 20),
  };
  std::unique_ptr<ExpressionAstNode> parseIntegerExpression(std::istream&);
  std::unique_ptr<ExpressionAstNode> parseIdentifierExpression(std::istream&);
  std::unique_ptr<ExpressionAstNode> parsePrimaryExpression(std::istream&);
  std::unique_ptr<ExpressionAstNode> parseBinaryExpression(std::istream&, std::int64_t, std::unique_ptr<ExpressionAstNode>);
};

#endif  // !PARSER_H
