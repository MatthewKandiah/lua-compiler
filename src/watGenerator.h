#include "parser.h"
class WatGenerator {
public:
  WatGenerator(Parser p): parser {std::move(p)} {};

  // damn, we're going to want to make BaseParser and MockParser to make testing this less painful
  // probably going to need some sort of AST test factory too
  Parser parser;
};
