#include "RandomSymbol.h"

#include <cstdlib>
#include <ctime>

#define MAX_SYMBOL 36
#define AL_SYMBOL 26

RandomSymbol::RandomSymbol() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}
char RandomSymbol::getRandomSymbol() const {
  int choice_symbol = std::rand() % MAX_SYMBOL;
  if (choice_symbol < AL_SYMBOL) {
    return static_cast<char>('a' + choice_symbol);
  } else {
    return static_cast<char>('0' + (choice_symbol - AL_SYMBOL));
  }
}
