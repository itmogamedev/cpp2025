#pragma once

struct GameConfig {
  unsigned int w = 1280;
  unsigned int h = 960;
  int n = 5;
  float r = 40.f;
  float time_limit = 30.f;
  float miss_penalty = 2.f;
};

void runGame(const GameConfig& cfg);
