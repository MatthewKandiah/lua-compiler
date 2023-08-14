#include "parser.h"
#include <ostream>
#include <string>
class WatGenerator {
public:
  WatGenerator(std::shared_ptr<std::ostream> o, std::unique_ptr<BaseParser> p)
      : outStreamPtr{o}, parserPtr{std::move(p)} {};
  void generate();

private:
  std::shared_ptr<std::ostream> outStreamPtr;
  std::unique_ptr<BaseParser> parserPtr;
  void generateInit();
  void generateFinish();
};
