#ifndef PARSER_H
#define PARSER_H

#include "astNode.h"
#include "token.h"
#include "tokenType.h"
#include <cstdint>
#include <istream>
class Parser {
public:
  Parser(std::istream &inputStream): currentToken{TokenType::illegal, ""} {currentToken = getNextToken(inputStream);} ;

  Token currentToken;
  Token getNextToken(std::istream &);
  AstExpressionNode parseExpression(std::istream &);
  AstExpressionNode parsePrimaryExpression();
  std::int64_t getOperatorPrecedence(char op);

};

#endif // !PARSER_H
