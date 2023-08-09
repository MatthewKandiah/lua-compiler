#ifndef PARSER_H
#define PARSER_H

#include "astNode.h"
#include "lexer.h"
#include "token.h"
#include "tokenType.h"
#include <cstdint>
#include <istream>
#include <memory>
#include <vector>

class BaseParser {
public:
  virtual std::unique_ptr<AstExpressionNode> parseExpression() = 0;
};

class Parser : public BaseParser {
public:
  Parser(std::unique_ptr<BaseLexer> l)
      : lexerPtr{std::move(l)}, currentToken{lexerPtr->getNextToken()} {};
  std::unique_ptr<AstExpressionNode> parseExpression() override;

private:
  std::unique_ptr<BaseLexer> lexerPtr;
  Token currentToken;
  std::unique_ptr<AstExpressionNode> parsePrimaryExpression();
  std::unique_ptr<AstExpressionNode>
      parseBinaryExpressionRhs(std::int64_t,
                               std::unique_ptr<AstExpressionNode>);
  std::int64_t getOperatorPrecedence(Token);
  std::string tokenTypeToBinaryOperatorString(TokenType);
};

class MockParser : public BaseParser {
public:
    MockParser() {
        // TODO - work out how we're going to pass in our nodes and return them sensibly for tests
    };
};

#endif // !PARSER_H
