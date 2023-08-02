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
    std::cerr << "Lexer emits eof" << '\n';
    return Token(TokenType::eof, "");
  }

  Token result = Token(TokenType::illegal, "");
  switch (lastCharacter) {
  case '=':
    result = Token(TokenType::equals, "");
    std::cerr << "Lexer emits equals" << '\n';
    break;
  case '+':
    result = Token(TokenType::plus, "");
    std::cerr << "Lexer emits plus" << '\n';
    break;
  case '-':
    result = Token(TokenType::minus, "");
    std::cerr << "Lexer emits minus" << '\n';
    break;
  case '(':
    result = Token(TokenType::leftBracket, "");
    std::cerr << "Lexer emits leftBracket" << '\n';
    break;
  case ')':
    result = Token(TokenType::rightBracket, "");
    std::cerr << "Lexer emits rightBracket" << '\n';
    break;
  }
  if (result.type != TokenType::illegal) {
    lastCharacter = characterStream.get();
    return result;
  }

  if (std::isalpha(lastCharacter)) {
    std::string buffer{lastCharacter};
    lastCharacter = characterStream.get();
    while (std::isalnum(lastCharacter)) {
      buffer.push_back(lastCharacter);
      lastCharacter = characterStream.get();
    }
    if (buffer == std::string("local")) {
      std::cerr << "Lexer emits keyword local" << '\n';
      return Token(TokenType::local, "");
    } else {
      std::cerr << "Lexer emits identifier " << buffer << '\n';
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
    std::cerr << "Lexer emits integer " << buffer << '\n';
    return Token(TokenType::integer, buffer);
  }

  std::cerr << "Lexer emits illegal " << '\n';
  return Token(TokenType::illegal, std::string(1, lastCharacter));
}
