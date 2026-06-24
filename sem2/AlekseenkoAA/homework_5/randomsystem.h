#pragma once

#include <random>

class RandomSystem {
 public:
  RandomSystem();
  float randomFloat(float min_value, float max_value);
  int randomInt(int min_value, int max_value);

 private:
  std::mt19937 engine;
};
