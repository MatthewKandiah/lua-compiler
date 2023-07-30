#include "lexer.h"
#include <cctype>
#include <iostream>
#include <istream>
#include <string>

Token Lexer::getNextToken(std::istream &characterStream) {
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
    std::string buffer{lastCharacter};
    lastCharacter = characterStream.get();
    while (std::isalnum(lastCharacter)) {
      buffer.push_back(lastCharacter);
      lastCharacter = characterStream.get();
    }
    if (buffer == std::string("local")) {
      return Token(TokenType::local, "");
    } else {
      return Token(TokenType::identifier, buffer);
    }
    buffer.clear();
  }

  if (std::isdigit(lastCharacter)) {
    std::string buffer{lastCharacter};
    lastCharacter = characterStream.get();
    while (std::isdigit(lastCharacter)) {
      buffer.push_back(lastCharacter);
      lastCharacter = characterStream.get();
    }
    return Token(TokenType::integer, buffer);
  }

  return Token(TokenType::illegal, std::string(1, lastCharacter));
}
