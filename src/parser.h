#include <istream>

#include "lexer.h"
#include "token.h"
#include "tokenType.h"
#include "astNode.h"

class Parser {
 public:
  Parser(Lexer l) : lexer {l}, currentToken{Token(TokenType::illegal, "")} {}

    std::unique_ptr<ExpressionAstNode> parseIntegerExpression(std::istream&);

 private:
  Lexer lexer;
  Token currentToken;
  void getNextToken(std::istream&);
};
