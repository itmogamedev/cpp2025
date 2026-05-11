#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(float width, float height, float maxVelocity)
    : rng((unsigned)time(nullptr)),
      ux(0.f, width),
      uy(0.f, height),
      uv(-maxVelocity, maxVelocity) {}

float RandomGenerator::randomX() { return ux(rng); }
float RandomGenerator::randomY() { return uy(rng); }
float RandomGenerator::randomVelocity() { return uv(rng); }
