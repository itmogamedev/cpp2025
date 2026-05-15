#include "controller.h"

int main() {
  const unsigned int WINDOW_WIDTH = 800;
  const unsigned int WINDOW_HEIGHT = 600;
  Controller game(WINDOW_WIDTH, WINDOW_HEIGHT, "OSU Doma");
  game.run();
  return 0;
}
