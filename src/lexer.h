#ifndef LEXER_H
#define LEXER_H
#include <istream>

#include "token.h"

class Lexer {
public:
  Lexer(std::istream& inputStream): inputStreamPtr {&inputStream} {};
  Token getNextToken();

private:
  std::istream* inputStreamPtr;
  char lastCharacter{' '};
};

#endif // !LEXER_H
