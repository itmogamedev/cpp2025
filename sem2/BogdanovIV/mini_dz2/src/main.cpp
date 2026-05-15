#include <iostream>

#include "game.h"

int main() {
  try {
    TypingGame game;
    game.Run();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
