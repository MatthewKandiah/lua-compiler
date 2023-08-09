#ifndef LEXER_H
#define LEXER_H
#include <istream>
#include <vector>

#include "token.h"

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
  MockLexer(std::vector<Token> t): tokens{t} {}
  Token getNextToken() override {
    Token nextToken = tokens.at(nextTokenIndex);
    nextTokenIndex++;
    return nextToken;
  }
  int nextTokenIndex = 0;
  std::vector<Token> tokens;
};

#endif // !LEXER_H
