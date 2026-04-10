#include "randomSystem.h"

Randomizer::Randomizer() {
  std::random_device device;
  engine.seed(device());
}

float Randomizer::random(float min_value, float max_value) {
  // Проверяем корректность аргументов
  assert(min_value < max_value);
  std::uniform_real_distribution<float> distribution(min_value, max_value);
  return distribution(engine);
}

sf::Color Randomizer::randomColor() {
  return sf::Color(random(0, 255), random(0, 255), random(0, 255));
}
