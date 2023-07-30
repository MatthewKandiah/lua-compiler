#ifndef LEXER_H
#define LEXER_H
#include <istream>

#include "token.h"

class Lexer {
public:
  Token getNextToken(std::istream &);

private:
  char lastCharacter{' '};
};

#endif // !LEXER_H
