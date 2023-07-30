#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H
enum class TokenType {
  eof,
  illegal,
  identifier,
  integer,
  // symbols
  equals,        // =
  plus,          // +
  minus,         // -
  leftBracket,   // (
  rightBracket,  // )
  // keywords
  local,
};
#endif
