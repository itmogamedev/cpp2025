#include "symbol.h"

#include <cstdlib>
#include <ctime>

#include "constants.h"

SymbolGenerator::SymbolGenerator() : seeded(false) {
  if (!seeded) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    seeded = true;
  }
}

char SymbolGenerator::generate() {
  int randomNum = std::rand() % Constants::SYMBOL_COUNT;
  return 'a' + randomNum;
}
