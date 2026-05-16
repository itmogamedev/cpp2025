#include <cstdlib>
#include <ctime>

#include "GameSession.h"

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  GameSession session;
  session.launch();
  return 0;
}
