#ifndef PARSER_H
#define PARSER_H

#include "astNode.h"
#include "token.h"
#include "tokenType.h"
#include <istream>
class Parser {
public:
  Parser(std::istream &inputStream): currentToken{TokenType::illegal, ""} {currentToken = getNextToken(inputStream);} ;

  Token currentToken;
  Token getNextToken(std::istream &);
  AstExpressionNode parseExpression(std::istream &);
  AstExpressionNode parsePrimaryExpression();

};

#endif // !PARSER_H
