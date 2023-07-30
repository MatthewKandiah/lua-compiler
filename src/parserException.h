#ifndef PARSER_EXCEPTION_H
#define PARSER_EXCEPTION_H

#define PARSER
#include <exception>
#include <format>
#include <string>

#include "tokenType.h"
class InvalidTokenTypeException : public std::exception {
 public:
  InvalidTokenTypeException(TokenType e, TokenType rt, std::string rv)
      : expectedTokenType{e}, receivedTokenType{rt}, receivedValue{rv} {}
  TokenType expectedTokenType, receivedTokenType;
  std::string receivedValue;
};

#endif  // !PARSER_EXCEPTION_H
