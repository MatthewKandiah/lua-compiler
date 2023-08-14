#include "watGenerator.h"

void WatGenerator::generate() {
  generateInit();
  generateFinish();
}

void WatGenerator::generateInit() { *outStreamPtr << "(module "; };
void WatGenerator::generateFinish() { *outStreamPtr << ")"; };
