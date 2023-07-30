#ifndef LEXER_H
#define LEXER_H
#include <istream>
#include <memory>

#include "token.h"

class Lexer {
 public:
  Lexer(std::istream* cs) : characterStream{cs} {};

  std::istream* characterStream;

  Token getNextToken();

 private:
  char lastCharacter{' '};
};

#endif  // !LEXER_H
