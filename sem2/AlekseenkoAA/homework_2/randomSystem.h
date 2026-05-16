#pragma once
#include <SFML/Graphics/Color.hpp>
#include <cassert>
#include <random>

class Randomizer {
 private:
  std::mt19937 engine;

 public:
  Randomizer();
  ~Randomizer() = default;

  float random(float min_value, float max_value);

  sf::Color randomColor();
};