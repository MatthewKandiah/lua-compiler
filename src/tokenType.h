#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
#include <string>
enum class TokenType {
  eof,
  illegal,
  identifier,
  integer,
  // symbols
  equals,       // =
  plus,         // +
  minus,        // -
  leftBracket,  // (
  rightBracket, // )
  // keywords
  local,
};

inline std::string tokenTypeToString(TokenType t) {
  switch (t) {
  case TokenType::eof:
    return "eof";
  case TokenType::illegal:
    return "illegal";
  case TokenType::identifier:
    return "identifier";
  case TokenType::integer:
    return "integer";
  case TokenType::equals:
    return "equals";
  case TokenType::plus:
    return "plus";
  case TokenType::minus:
    return "minus";
  case TokenType::leftBracket:
    return "leftBracket";
  case TokenType::rightBracket:
    return "rightBracket";
  case TokenType::local:
    return "local";
  }
}
#endif
