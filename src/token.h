#ifndef TOKEN_H
#define TOKEN_H
#include "tokenType.h"
#include <algorithm>
#include <string>

class Token {
public:
	Token(TokenType t, const std::string& v): 
		type {t},
		value {std::move(v)}
		{}

	TokenType type;
	std::string value;
};

#endif
