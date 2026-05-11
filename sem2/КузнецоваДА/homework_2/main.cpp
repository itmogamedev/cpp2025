#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>

int main() {
  std::srand(std::time(nullptr));
  Game game;
  game.start();
  return 0;
}