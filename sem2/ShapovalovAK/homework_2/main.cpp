#include "Game.h"

int main() {
  GameConfig cfg;
  cfg.w = 1280;
  cfg.h = 960;
  cfg.n = 5;
  cfg.r = 40.f;
  cfg.time_limit = 30.f;
  cfg.miss_penalty = 2.f;
  runGame(cfg);
  return 0;
}
