#pragma once

#include <random>

class RandomGenerator {
 public:
  RandomGenerator(float width, float height, float maxVelocity = 200.f);
  float randomX();
  float randomY();
  float randomVelocity();

 private:
  std::mt19937 rng;
  std::uniform_real_distribution<float> ux;
  std::uniform_real_distribution<float> uy;
  std::uniform_real_distribution<float> uv;
};
