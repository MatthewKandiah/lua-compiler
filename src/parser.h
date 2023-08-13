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
  virtual ~BaseParser() = default;
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
  MockParser(std::vector<std::unique_ptr<AstExpressionNode>> v)
      : expressionPtrs{std::move(v)} {};
  std::vector<std::unique_ptr<AstExpressionNode>> expressionPtrs;
  int expressionIndex = 0;
  std::unique_ptr<AstExpressionNode> parseExpression() override {
    if (expressionIndex >= expressionPtrs.size()) {
      return NULL;
    }
    return std::move(expressionPtrs.at(expressionIndex++));
  }
};

#endif // !PARSER_H
