#include "lexer.h"
#include "tokenFactory.h"
#include <cctype>
#include <iostream>
#include <istream>
#include <string>

Token Lexer::getNextToken() {
  while (std::isspace(lastCharacter)) {
    lastCharacter = inputStreamPtr->get();
  }

  if (!(*inputStreamPtr)) {
    return tokenFactory::eof();
  }

  Token result = tokenFactory::illegal();
  switch (lastCharacter) {
  case '=':
    result = tokenFactory::equals();
    break;
  case '+':
    result = tokenFactory::plus();
    break;
  case '-':
    result = tokenFactory::minus();
    break;
  case '(':
    result = tokenFactory::leftBracket();
    break;
  case ')':
    result = tokenFactory::rightBracket();
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
      return tokenFactory::local();
    } else {
      return tokenFactory::identifier(buffer);
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
    return tokenFactory::integer(buffer);
  }

  return tokenFactory::illegal();
}
