#ifndef PARSER_H
#define PARSER_H

#include <istream>

#include "astNode.h"
#include "lexer.h"
#include "token.h"
#include "tokenType.h"

class Parser {
 public:
  Parser(Lexer l) : lexer{l}, currentToken{Token(TokenType::illegal, "")} {}

  std::unique_ptr<ExpressionAstNode> parseIntegerExpression(std::istream&);
  std::unique_ptr<ExpressionAstNode> parseIdentifierExpression(std::istream&);

 private:
  Lexer lexer;
  Token currentToken;
  void getNextToken(std::istream&);
};

#endif  // !PARSER_H
