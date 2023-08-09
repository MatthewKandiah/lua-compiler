#ifndef PARSER_H
#define PARSER_H

#include "astNode.h"
#include "lexer.h"
#include "token.h"
#include "tokenType.h"
#include <cstdint>
#include <istream>
class Parser {
public:
  Parser(BaseLexer* l): lexerPtr{std::move(l)}, currentToken{lexerPtr->getNextToken()} {} ;

  BaseLexer* lexerPtr;
  Token currentToken;
  Token getNextToken();
  std::unique_ptr<AstExpressionNode> parseExpression();
  std::unique_ptr<AstExpressionNode> parsePrimaryExpression();
  std::unique_ptr<AstExpressionNode> parseBinaryExpressionRhs(std::int64_t, std::unique_ptr<AstExpressionNode>);
  std::int64_t getOperatorPrecedence(Token);
  std::string tokenTypeToBinaryOperatorString(TokenType);
};

#endif // !PARSER_H
