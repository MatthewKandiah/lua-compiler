#include "lexer.h"
#include <istream>

Token Lexer::getNextToken(std::istream& characterStream) {
  while (std::isspace(lastCharacter)) {
    lastCharacter = characterStream.get();
  }

  if (!characterStream) {
    return Token(TokenType::eof, "");
  }

  switch (lastCharacter) {
    case '=':
      return Token(TokenType::equals, "");
    case '+':
      return Token(TokenType::plus, "");
    case '-':
      return Token(TokenType::minus, "");
    case '(':
      return Token(TokenType::leftBracket, "");
    case ')':
      return Token(TokenType::rightBracket, "");
  }

  if (std::isalpha(lastCharacter)) {
    // could be an identifier or a keyword
  }

  if (std::isdigit(lastCharacter)) {
    // got the start of a number
  }

  return Token(TokenType::illegal, std::string(1, lastCharacter));
}
