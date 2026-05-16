#include <iostream>

#include "Game.h"

int main() {
  try {
    Game game;
    game.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
