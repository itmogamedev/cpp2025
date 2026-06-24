#include "game.h"

int main(int argc, char** argv) {
  Game game;
  if (!game.load()) {
    return 1;
  }
  return game.run();
}
