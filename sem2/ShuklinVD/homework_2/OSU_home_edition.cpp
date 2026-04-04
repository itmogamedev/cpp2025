#include <cstdlib>
#include <ctime>

#include "game_controller.h"

int main() {
  srand(time(0));
  GameController control;
  control.run();
  return 0;
}
