#ifndef LEXER_H
#define LEXER_H
#include <istream>
#include <vector>

#include "token.h"

class BaseLexer {
public: 
  virtual Token getNextToken() = 0;
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
  int nextTokenIndex = 0;
  std::vector<Token> tokens;
};

#endif // !LEXER_H
