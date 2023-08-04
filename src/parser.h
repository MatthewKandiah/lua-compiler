#ifndef PARSER_H
#define PARSER_H

#include "astNode.h"
#include "lexer.h"
#include "token.h"
#include "tokenType.h"
#include <cstdint>
#include <istream>
#include <sys/wait.h>
class Parser {
public:
  Parser(std::istream &inputStream): currentToken{TokenType::illegal, ""} {currentToken = getNextToken(inputStream);} ;

  Lexer lexer {};
  Token currentToken;
  Token getNextToken(std::istream &);
  std::unique_ptr<AstExpressionNode> parseExpression(std::istream &);
  std::unique_ptr<AstExpressionNode> parsePrimaryExpression(std::istream &);
  std::unique_ptr<AstExpressionNode> parseBinaryExpressionRhs(std::istream &, std::int64_t, std::unique_ptr<AstExpressionNode>);
  std::int64_t getOperatorPrecedence(Token);
  std::string tokenTypeToBinaryOperatorString(TokenType);
};

#endif // !PARSER_H
