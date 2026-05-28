#include "randomsystem.h"

#include <ctime>

RandomSystem::RandomSystem() { engine.seed(unsigned(std::time(nullptr))); }

float RandomSystem::randomFloat(float min_value, float max_value) {
  float value = float(engine() % 100000u) / 99999.0f;
  return min_value + (max_value - min_value) * value;
}

int RandomSystem::randomInt(int min_value, int max_value) {
  int distance = max_value - min_value + 1;
  return min_value + int(engine() % unsigned(distance));
}
