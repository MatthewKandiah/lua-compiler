#include "lexer.h"
#include <cctype>
#include <iostream>
#include <istream>
#include <string>

Token Lexer::getNextToken() {
  while (std::isspace(lastCharacter)) {
    lastCharacter = inputStreamPtr->get();
  }

  if (!(*inputStreamPtr)) {
    return Token(TokenType::eof, "");
  }

  Token result = Token(TokenType::illegal, "");
  switch (lastCharacter) {
  case '=':
    result = Token(TokenType::equals, "");
    break;
  case '+':
    result = Token(TokenType::plus, "");
    break;
  case '-':
    result = Token(TokenType::minus, "");
    break;
  case '(':
    result = Token(TokenType::leftBracket, "");
    break;
  case ')':
    result = Token(TokenType::rightBracket, "");
    break;
  }
  if (result.type != TokenType::illegal) {
    lastCharacter = inputStreamPtr->get();
    return result;
  }

  if (std::isalpha(lastCharacter)) {
    std::string buffer{lastCharacter};
    lastCharacter = inputStreamPtr->get();
    while (std::isalnum(lastCharacter)) {
      buffer.push_back(lastCharacter);
      lastCharacter = inputStreamPtr->get();
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
    lastCharacter = inputStreamPtr->get();
    while (std::isdigit(lastCharacter)) {
      buffer.push_back(lastCharacter);
      lastCharacter = inputStreamPtr->get();
    }
    return Token(TokenType::integer, buffer);
  }

  return Token(TokenType::illegal, std::string(1, lastCharacter));
}
