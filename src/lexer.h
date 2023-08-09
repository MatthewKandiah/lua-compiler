#ifndef LEXER_H
#define LEXER_H
#include <istream>
#include <vector>

#include "token.h"
#include "tokenType.h"

class BaseLexer {
public: 
  virtual Token getNextToken() = 0;
  virtual ~BaseLexer() = default;
};

class Lexer : public BaseLexer {
public:
  Lexer(std::istream& inputStream): inputStreamPtr {&inputStream} {}
  Token getNextToken() override;

private:
  std::istream* inputStreamPtr;
  char lastCharacter{' '};
};

class MockLexer : public BaseLexer {
public:
  MockLexer(std::vector<Token> t): tokens{std::move(t)} {}
  Token getNextToken() override {
    if (currentToken.type == TokenType::eof) {
      // once we return eof we expect to keep returning it whenever asked
      return currentToken;
    }
    currentToken = tokens.at(nextTokenIndex);
    nextTokenIndex++;
    return currentToken;
  }
  Token currentToken {TokenType::illegal, ""};
  int nextTokenIndex = 0;
  std::vector<Token> tokens;
};

#endif // !LEXER_H
