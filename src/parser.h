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
  std::unique_ptr<AstExpressionNode> parseExpression(std::istream &);
  std::unique_ptr<AstExpressionNode> parsePrimaryExpression(std::istream &);
  std::unique_ptr<AstExpressionNode> parseBinaryExpressionRhs(std::istream &, std::int64_t, std::unique_ptr<AstExpressionNode>);
  std::int64_t getOperatorPrecedence(std::string);

};

#endif // !PARSER_H
