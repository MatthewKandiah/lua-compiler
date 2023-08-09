#ifndef TOKEN_FACTORY_H
#define TOKEN_FACTORY_H

#include "token.h"
#include <string>

namespace tokenFactory {
inline Token eof() { return Token(TokenType::eof, ""); }

inline Token plus() { return Token(TokenType::plus, ""); }

inline Token minus() { return Token(TokenType::minus, ""); }

inline Token equals() { return Token(TokenType::equals, ""); }

inline Token illegal() { return Token(TokenType::illegal, ""); }

inline Token leftBracket() { return Token(TokenType::leftBracket, ""); }

inline Token rightBracket() { return Token(TokenType::rightBracket, ""); }

inline Token local() {return Token(TokenType::local, ""); }

inline Token identifier(std::string name) {
  return Token(TokenType::identifier, name);
}

inline Token integer(std::string value) {
  return Token(TokenType::integer, value);
}

inline Token integer(int value) {
  return Token(TokenType::integer, std::to_string(value));
}
} // namespace tokenFactory

#endif // !TOKEN_FACTORY_H
